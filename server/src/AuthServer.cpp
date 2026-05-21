#include "AuthServer.hpp"

AuthServer::AuthServer() {}

// BUG: Hardcoded to always return true! Massive security flaw.
bool AuthServer::authorizeBadge(int badgeId) const {
    // Team must implement a real lookup against a list of valid IDs
    return true; 
}
