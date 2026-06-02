# ==============================================================================
# Embedded Smart Card Reader Build Configuration
# ==============================================================================

# Define the target as a STATIC library.
add_library(embedded_logic STATIC
    src/DoorReader.cpp
)

# Define the include directories.
target_include_directories(embedded_logic PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ==============================================================================
# Unit Tests (Google Test)
# ==============================================================================

# 1. Create the test executable
add_executable(embedded_logic_tests
    tests/DoorReaderTest.cpp
)

# 2. Link the embedded library and Google Test
target_link_libraries(embedded_logic_tests PRIVATE
    embedded_logic
    gtest_main
)

# 3. Give the test executable access to the headers
target_include_directories(embedded_logic_tests PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 4. Register the test with CMake so `ctest` can find it
add_test(NAME embedded_logic_tests COMMAND embedded_logic_tests)

# ==============================================================================
# Embedded Executable
# ==============================================================================
add_executable(embedded_app src/main.cpp)

# Link the DoorReader logic, HTTP library, and JSON library
target_link_libraries(embedded_app PRIVATE
    embedded_logic
    httplib
    nlohmann_json::nlohmann_json
)
target_include_directories(embedded_app PRIVATE include)

# Add OpenSSL Security
find_package(OpenSSL REQUIRED)
target_link_libraries(embedded_app PRIVATE OpenSSL::SSL OpenSSL::Crypto)
