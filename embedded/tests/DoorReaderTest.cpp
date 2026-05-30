#include "DoorReader.hpp"
#include <gtest/gtest.h>

// Test 1: Verify the constructor sets the correct default state
TEST(DoorReaderTest, InitialStateIsLocked) {
    const DoorReader reader; 
    EXPECT_EQ(reader.getState(), DoorState::LOCKED);
    EXPECT_EQ(reader.getFailedAttempts(), 0);
}

// Test 2: Verify a successful scan unlocks the door and resets attempts
TEST(DoorReaderTest, SuccessfulScanUnlocksDoor) {
    DoorReader reader; 
    
    // Simulate a failed attempt first to ensure the counter resets
    reader.processScanResult(false);
    EXPECT_EQ(reader.getFailedAttempts(), 1);

    // Simulate a successful scan
    reader.processScanResult(true);
    
    EXPECT_EQ(reader.getState(), DoorState::UNLOCKED);
    EXPECT_EQ(reader.getFailedAttempts(), 0);
}

// Test 3: Verify a failed scan increments the counter but keeps the door locked
TEST(DoorReaderTest, FailedScanIncrementsCounter) {
    DoorReader reader; 
    
    reader.processScanResult(false);
    
    EXPECT_EQ(reader.getState(), DoorState::LOCKED);
    EXPECT_EQ(reader.getFailedAttempts(), 1);
}

// Test 4: Verify the 3rd consecutive failure triggers the ALARM_LOCKOUT
TEST(DoorReaderTest, ThirdFailedScanTriggersLockout) {
    DoorReader reader; 
    
    reader.processScanResult(false); // Attempt 1
    EXPECT_EQ(reader.getState(), DoorState::LOCKED);
    
    reader.processScanResult(false); // Attempt 2
    EXPECT_EQ(reader.getState(), DoorState::LOCKED);
    
    reader.processScanResult(false); // Attempt 3
    EXPECT_EQ(reader.getState(), DoorState::ALARM_LOCKOUT);
    EXPECT_EQ(reader.getFailedAttempts(), 3);

    // Ensure it stays locked out on subsequent scans
    reader.processScanResult(true); 
    EXPECT_EQ(reader.getState(), DoorState::ALARM_LOCKOUT);
}

// Test 5: Verify secureDoor() forces the state back to LOCKED
TEST(DoorReaderTest, SecureDoorForcesLockedState) {
    DoorReader reader; 
    
    // Unlock the door first
    reader.processScanResult(true);
    EXPECT_EQ(reader.getState(), DoorState::UNLOCKED);
    
    // Force secure
    reader.secureDoor();
    
    EXPECT_EQ(reader.getState(), DoorState::LOCKED);
}

// Test 6: Lockout state ignores valid badges
TEST(DoorReaderTest, LockoutStateIgnoresValidBadges) {
    DoorReader reader; 
    
    // 1. Force the door into the ALARM_LOCKOUT state
    reader.processScanResult(false);
    reader.processScanResult(false);
    reader.processScanResult(false);
    EXPECT_EQ(reader.getState(), DoorState::ALARM_LOCKOUT);

    // 2. Attempt to scan a VALID badge
    reader.processScanResult(true);

    // 3. Verify the door strictly remains locked out and the counter doesn't reset
    EXPECT_EQ(reader.getState(), DoorState::ALARM_LOCKOUT);
    EXPECT_EQ(reader.getFailedAttempts(), 3); 
}