#include "DoorReader.hpp"
#include <chrono>
#include <httplib.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>

constexpr int VALID_BADGE = 1001;
constexpr int INVALID_BADGE = 9999;
constexpr int HTTP_OK = 200;
constexpr int HTTP_UNAUTHORIZED = 401;
constexpr int DELAY_MS = 500;
constexpr int SECURE_PORT = 8443;
constexpr const char* AUTH_TOKEN = "labtoken123";

// Template used to accept the secure SSLClient
template <typename ClientType>
void simulateBadgeTap(int badgeId, ClientType& cli, DoorReader& reader) {
    std::cout << "\n[EMBEDDED] Tapping badge " << badgeId << "...\n";

    nlohmann::json reqPayload;
    reqPayload["badge_id"] = badgeId;

    // SECURITY: Attach the API Key
    httplib::Headers headers = {
        {"Authorization", std::string("Bearer ") + AUTH_TOKEN}
    };

    if (auto res = cli.Post("/access", headers, reqPayload.dump(), "application/json")) {
        if (res->status == HTTP_OK) {
            auto body = nlohmann::json::parse(res->body);
            bool granted = body["granted"];

            reader.processScanResult(granted);

            if (reader.getState() == DoorState::UNLOCKED) {
                std::cout << "[EMBEDDED] Door Unlocked! Green LED ON.\n";
            } else if (reader.getState() == DoorState::ALARM_LOCKOUT) {
                std::cout << "[EMBEDDED] ALARM TRIGGERED! System Lockout. Red LED FLASHING.\n";
            } else {
                std::cout << "[EMBEDDED] Access Denied! Red LED ON.\n";
            }
        } else if (res->status == HTTP_UNAUTHORIZED) {
            std::cerr << "[EMBEDDED] Network Error: 401 Unauthorized (Bad API Key)\n";
        }
    } else {
        std::cerr << "[EMBEDDED] Error - Could not reach the server!\n";
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_MS));
}

int main() {
    try {
        DoorReader reader;
        httplib::SSLClient cli("127.0.0.1", SECURE_PORT);
        cli.enable_server_certificate_verification(false); // Trust self-signed cert

        std::cout << "--- STARTING SECURE TLS TEST ---\n";

        // Run the intruder simulation
        simulateBadgeTap(INVALID_BADGE, cli, reader);
        simulateBadgeTap(INVALID_BADGE, cli, reader);
        simulateBadgeTap(INVALID_BADGE, cli, reader);

        std::cout << "\n[SIMULATION] Intruder stole a valid badge. Trying it during lockout...\n";
        simulateBadgeTap(VALID_BADGE, cli, reader); 

        std::cout << "\n[SIMULATION] Administrator arrived. Resetting system...\n";
        reader.adminReset();
        std::cout << "[EMBEDDED] System reset to LOCKED state.\n";

        std::cout << "\n[SIMULATION] Normal employee arrives for work...\n";
        simulateBadgeTap(VALID_BADGE, cli, reader);

        std::cout << "\n--- SECURITY TEST COMPLETE ---\n";

    } catch (...) {
        std::cerr << "[EMBEDDED] Fatal exception occurred!\n";
        return 1;
    }
    return 0;
}
