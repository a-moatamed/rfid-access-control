#pragma once

enum class DoorState { LOCKED, UNLOCKED, ALARM_LOCKOUT };

class DoorReader {
private:
    DoorState state;
    int failedAttempts;

public:
    DoorReader();
    
    DoorState getState() const;
    int getFailedAttempts() const;

    // TODO: Implement security logic
    void processScanResult(bool isAuthorized);
    void secureDoor();
};
