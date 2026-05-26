#include "AuthServer.hpp"

AuthServer::AuthServer() = default;

// BUG: Hardcoded to always return true! Massive security flaw.
// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
bool AuthServer::authorizeBadge(int badgeId) const {
    // Team must implement a real lookup against a list of valid IDs
    if(badgeId < 0) {  // just a simple check to prevent negative IDs, but this is not sufficient for real security
        return false; 
    }

    // For now, we'll just return false to simulate a failed authorization
    return false; 
}
