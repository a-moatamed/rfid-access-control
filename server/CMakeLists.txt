# ==============================================================================
# Project:      [rfid-access-control/server]
# Description:  CMake configuration for the authentication server library.
# ==============================================================================

add_library(auth_server_lib STATIC src/AuthServer.cpp)
target_include_directories(auth_server_lib PUBLIC include)

add_executable(auth_server_tests
    tests/AuthServerTest.cpp
)

target_link_libraries(auth_server_tests PRIVATE
    auth_server_lib
    GTest::gtest_main
)

target_include_directories(auth_server_tests PRIVATE include)

add_test(NAME auth_server_tests COMMAND auth_server_tests)
