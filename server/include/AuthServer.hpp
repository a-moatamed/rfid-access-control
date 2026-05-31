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
     * Note: The server starts with an empty list of authorized badges. Badges must be added using addAuthorizedBadge() before they can be authorized.
     */
    AuthServer();

    /**
     * @brief Verifies whether a badge identifier is authorized.
     *
     * @param badgeId The numeric identifier of the badge being checked.
     * Note: Negative badge IDs are considered invalid and will be rejected.
     * @return True if the badge is authorized, false otherwise.
     */
    bool authorizeBadge(int badgeId) const;

    /**
     * @brief Adds a badge ID to the list of authorized badges.
     *
     * @param badgeId The numeric identifier of the badge to add.
     * Note: Adding a badge that is already authorized will not cause issues and will simply ensure it remains authorized.
     */
    void addAuthorizedBadge(int badgeId);

    /**
     * @brief Removes a badge ID from the list of authorized badges.
     *
     * @param badgeId The numeric identifier of the badge to remove.
     * Note: Removing a badge that is not currently authorized will not cause issues and will simply ensure it remains unauthorized.
     */
    void removeAuthorizedBadge(int badgeId);

};
