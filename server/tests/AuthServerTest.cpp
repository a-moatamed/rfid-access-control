#include <gtest/gtest.h>

#include "AuthServer.hpp"

const int id1 = 1001, id2 = 1002, id3 = 1003 , id4 = 2001, id5 = 2002, id6 = 2003; // Sample badge IDs for testing


// Test that the server accepts registered badges.

TEST(AuthServerTest, AcceptsRegisteredBadge) {
    AuthServer server;
    server.addAuthorizedBadge(id1);
    server.addAuthorizedBadge(id2);
    server.addAuthorizedBadge(id3);

    EXPECT_TRUE(server.authorizeBadge(id1));
    EXPECT_TRUE(server.authorizeBadge(id2));
    EXPECT_TRUE(server.authorizeBadge(id3));
}

// Test that the server rejects unregistered badges.

TEST(AuthServerTest, RejectsUnregisteredBadge) {
    AuthServer server;

    EXPECT_FALSE(server.authorizeBadge(9999));
    EXPECT_FALSE(server.authorizeBadge(1234));
}
// Test that the server rejects negative badge IDs.
TEST(AuthServerTest, RejectsNegativeBadgeId) {
    AuthServer server;
    EXPECT_FALSE(server.authorizeBadge(-1));
}

// Test that the server can add and remove badges correctly.
TEST(AuthServerTest, AddAndRemoveBadge) {
    AuthServer server;
    server.addAuthorizedBadge(id4);
    EXPECT_TRUE(server.authorizeBadge(id4));

    server.removeAuthorizedBadge(id4);
    EXPECT_FALSE(server.authorizeBadge(id4));
}

// Test that adding a duplicate badge does not cause issues and that the badge remains authorized.
TEST(AuthServerTest, AddDuplicateBadge) {
    AuthServer server;
    server.addAuthorizedBadge(id5);
    server.addAuthorizedBadge(id5); // Adding the same badge again should not cause issues
    EXPECT_TRUE(server.authorizeBadge(id5));
}

// Test that removing a non-existent badge does not cause issues and that the badge remains unauthorized.
TEST(AuthServerTest, RemoveNonExistentBadge) {
    AuthServer server;
    server.removeAuthorizedBadge(id6); // Removing a badge that doesn't exist should not cause issues
    EXPECT_FALSE(server.authorizeBadge(id6));
}