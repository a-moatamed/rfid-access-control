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
    gtest_main
)

target_include_directories(auth_server_tests PRIVATE include)

add_test(NAME auth_server_tests COMMAND auth_server_tests)

# ==============================================================================
# Server Executable
# ==============================================================================
add_executable(server_app src/main.cpp)

# Link the AuthServer logic, HTTP library, and JSON library
target_link_libraries(server_app PRIVATE
    auth_server_lib
    httplib
    nlohmann_json::nlohmann_json
)
target_include_directories(server_app PRIVATE include)


# Add OpenSSL Security
find_package(OpenSSL REQUIRED)
target_link_libraries(server_app PRIVATE OpenSSL::SSL OpenSSL::Crypto)