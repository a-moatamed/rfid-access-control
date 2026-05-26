#pragma once

/**
 * @brief Simulates the backend authorization server for badge validation.
 */
class AuthServer {
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

    // Justification: Will require class state in Epic 3 when the database is added.
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    bool authorizeBadge(int badgeId) const;
};
