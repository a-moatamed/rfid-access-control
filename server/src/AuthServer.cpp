#include <algorithm>
#include <array>

#include "AuthServer.hpp"

AuthServer::AuthServer() = default;

bool AuthServer::authorizeBadge(int badgeId) const {
    if (badgeId < 0) {
        return false;
    }

    return std::find(authorizedBadgeIds.begin(), authorizedBadgeIds.end(), badgeId) != authorizedBadgeIds.end();
}

void AuthServer::addAuthorizedBadge(int badgeId) {
    if (badgeId < 0) {
        return;
    }

    if (!authorizeBadge(badgeId)) {
        authorizedBadgeIds.push_back(badgeId);
    }
}

void AuthServer::removeAuthorizedBadge(int badgeId) {
    if (badgeId < 0) {
        return;
    }

    auto item = std::find(authorizedBadgeIds.begin(), authorizedBadgeIds.end(), badgeId);
    if (item != authorizedBadgeIds.end()) { // Badge found, remove it
        authorizedBadgeIds.erase(item);
    }
}
