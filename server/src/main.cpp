#include "AuthServer.hpp"
#include <httplib.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

constexpr int TEST_BADGE_1 = 1001;
constexpr int TEST_BADGE_2 = 1002;
constexpr int SECURE_PORT = 8443;
constexpr int HTTP_UNAUTHORIZED = 401;
constexpr const char* VALID_TOKEN = "labtoken123";

int main() {
    try {
        AuthServer authDb;
        authDb.addAuthorizedBadge(TEST_BADGE_1);
        authDb.addAuthorizedBadge(TEST_BADGE_2);

        // Initialize the SECURE HTTP network server
        httplib::SSLServer svr("../cert.pem", "../key.pem");

        if (!svr.is_valid()) {
            std::cerr << "[SERVER] SSL Server failed to start! Check certs.\n";
            return 1;
        }

        svr.Post("/access", [&authDb](const httplib::Request& req, httplib::Response& res) {
            
            // SECURITY CHECK: Verify the Bearer Token
            auto auth = req.get_header_value("Authorization");
            if (auth != std::string("Bearer ") + VALID_TOKEN) {
                res.status = HTTP_UNAUTHORIZED;
                res.set_content(R"({"error":"unauthorized"})", "application/json");
                std::cout << "[SERVER] SECURITY ALERT: Unauthorized access attempt blocked!\n";
                return;
            }

            // Normal Business Logic
            auto body = nlohmann::json::parse(req.body);
            int badgeId = body["badge_id"];

            bool isAllowed = authDb.authorizeBadge(badgeId);

            nlohmann::json responseJson;
            responseJson["granted"] = isAllowed;

            res.set_content(responseJson.dump(), "application/json");
            
            std::cout << "[SERVER] Scanned Badge: " << badgeId 
                      << " | Access: " << (isAllowed ? "GRANTED" : "DENIED") << "\n";
        });

        std::cout << "[SERVER] SECURE Listening on https://0.0.0.0:" << SECURE_PORT << "...\n";
        svr.listen("0.0.0.0", SECURE_PORT);
    } catch (...) {
        std::cerr << "[SERVER] Fatal exception occurred!\n";
        return 1;
    }
    return 0;
}