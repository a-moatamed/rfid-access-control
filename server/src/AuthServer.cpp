#include <algorithm>
#include <array>

#include "AuthServer.hpp"

AuthServer::AuthServer() = default;

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
bool AuthServer::authorizeBadge(int badgeId) const {
    if (badgeId < 0) {
        return false;
    }

    constexpr std::array<int, 3> allowedBadges{1001, 1002, 1003};

    return std::find(allowedBadges.begin(), allowedBadges.end(), badgeId) != allowedBadges.end();
}
