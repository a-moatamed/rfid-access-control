#pragma once
#include <vector>

/**
 * @brief Simulates the backend authorization server for badge validation.
 */
class AuthServer {
private:
    // Simulated list of authorized badge IDs
    std::vector<int> authorizedBadgeIds;
public:
    /**
     * @brief Constructs an authorization server instance.
     */
    AuthServer();

    /**
     * @brief Verifies whether a badge identifier is authorized.
     *
     * @param badgeId The numeric identifier of the badge being checked.
     * @return True if the badge is authorized, false otherwise.
     */
    bool authorizeBadge(int badgeId) const;

    /**
     * @brief Adds a badge ID to the list of authorized badges.
     *
     * @param badgeId The numeric identifier of the badge to add.
     */
    void addAuthorizedBadge(int badgeId);

    /**
     * @brief Removes a badge ID from the list of authorized badges.
     *
     * @param badgeId The numeric identifier of the badge to remove.
     */
    void removeAuthorizedBadge(int badgeId);

};
