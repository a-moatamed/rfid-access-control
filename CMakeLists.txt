cmake_minimum_required(VERSION 3.14)
project(DistributedAccessControl VERSION 1.0 LANGUAGES CXX)

# Enforce C++17 Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Download and configure Google Test globally via FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)

# Prevent GTest from overriding the compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Make GTest available to all subdirectories
FetchContent_MakeAvailable(googletest)

