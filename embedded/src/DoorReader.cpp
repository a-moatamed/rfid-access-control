#include "DoorReader.hpp"

DoorReader::DoorReader() : state(DoorState::LOCKED), failedAttempts(0) {}

DoorState DoorReader::getState() const { return state; }
int DoorReader::getFailedAttempts() const { return failedAttempts; }

// BUG: Does not trigger ALARM_LOCKOUT after 3 failed attempts
void DoorReader::processScanResult(bool isAuthorized) {
    if (isAuthorized) {
        state = DoorState::UNLOCKED;
        failedAttempts = 0;
    } else {
        state = DoorState::LOCKED;
        failedAttempts += 1;
    }
}

void DoorReader::secureDoor() {
    state = DoorState::LOCKED;
}
