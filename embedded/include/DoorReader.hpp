#pragma once

/**
 * @brief Represents the security state of the door controller.
 */
enum class DoorState {
    LOCKED,
    UNLOCKED,
    ALARM_LOCKOUT
};

/**
 * @brief Handles badge scan results and tracks door security state.
 *
 * The door reader starts in the locked state and counts failed
 * authorization attempts in order to support brute-force protection.
 */
class DoorReader {
private:
    DoorState state;
    int failedAttempts;

public:
    /**
     * @brief Constructs a door reader in the locked state.
     */
    DoorReader();

    /**
     * @brief Returns the current door state.
     *
     * @return The active state of the door reader.
     */
    DoorState getState() const;

    /**
     * @brief Returns the number of consecutive failed attempts.
     *
     * @return The current failed attempt counter.
     */
    int getFailedAttempts() const;

    /**
     * @brief Processes the result of a badge authorization attempt.
     *
     * @param isAuthorized True if the badge was accepted, false otherwise.
     */
    void processScanResult(bool isAuthorized);

    /**
     * @brief Forces the door back into a locked state.
     */
    void secureDoor();

    /**
     * @brief Clears an ALARM_LOCKOUT state and resets the door to LOCKED.
     */
    void adminReset();
};
