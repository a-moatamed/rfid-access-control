#include "DoorReader.hpp"

DoorReader::DoorReader() : state(DoorState::LOCKED), failedAttempts(0) {}

DoorState DoorReader::getState() const { return state; }

int DoorReader::getFailedAttempts() const { return failedAttempts; }

void DoorReader::processScanResult(bool isAuthorized) {
    // If we are already in lockout, do not process further scans
    if (state == DoorState::ALARM_LOCKOUT) {
        return; 
    }
    if (isAuthorized) {
        state = DoorState::UNLOCKED;
        failedAttempts = 0;
    } else {
        failedAttempts += 1;
        if (failedAttempts >= 3) {
            state = DoorState::ALARM_LOCKOUT;
        } else {
            state = DoorState::LOCKED;
        }
    }
}

void DoorReader::secureDoor() {
    state = DoorState::LOCKED;
    failedAttempts = 0; // FIXED: Ghost counter bug resolved
}

// NEW: Recovery mechanism for Epic 3.1
void DoorReader::adminReset() {
    state = DoorState::LOCKED;
    failedAttempts = 0;
}
