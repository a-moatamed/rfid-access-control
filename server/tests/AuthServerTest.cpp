#include <gtest/gtest.h>

#include "AuthServer.hpp"

TEST(AuthServerTest, AcceptsRegisteredBadge) {
    const AuthServer server;
    EXPECT_TRUE(server.authorizeBadge(1001));
    EXPECT_TRUE(server.authorizeBadge(1002));
    EXPECT_TRUE(server.authorizeBadge(1003));
}

TEST(AuthServerTest, RejectsUnregisteredBadge) {
    const AuthServer server;
    EXPECT_FALSE(server.authorizeBadge(9999));
    EXPECT_FALSE(server.authorizeBadge(1234));
}

TEST(AuthServerTest, RejectsNegativeBadgeId) {
    const AuthServer server;
    EXPECT_FALSE(server.authorizeBadge(-1));
}
