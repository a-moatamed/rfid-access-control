cmake_minimum_required(VERSION 3.14)
project(DistributedAccessControl VERSION 1.0 LANGUAGES CXX)
include(CTest)

option(ENABLE_COVERAGE "Enable coverage instrumentation" OFF)
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
if(ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        message(STATUS "Coverage instrumentation enabled")
        add_compile_options(-O0 -g --coverage)
        add_link_options(--coverage)
    else()
        message(WARNING "Coverage is only supported with GCC or Clang")
    endif()
endif()

find_program(GCOVR_EXECUTABLE gcovr)

if(GCOVR_EXECUTABLE)
    message(STATUS "Found gcovr: ${GCOVR_EXECUTABLE}")
else()
    message(WARNING "gcovr not found. Install with: sudo apt install gcovr")
endif()
# Search the host operating system for the clang-tidy executable 
find_program(CLANG_TIDY_EXE NAMES clang-tidy)

if(CLANG_TIDY_EXE)
    message(STATUS "Found clang-tidy: ${CLANG_TIDY_EXE}")
    # Enable all standard checks, disable noisy/compiler-specific ones.
    set(CMAKE_CXX_CLANG_TIDY 
        "${CLANG_TIDY_EXE};-checks=*,-fuchsia-*,-llvmlibc-*,-llvm-header-guard,-modernize-use-trailing-return-type;--warnings-as-errors=*"
    )
else()
    message(WARNING "clang-tidy not found. Install with: sudo apt install clang-tidy")
endif()

# Add project components
add_subdirectory(embedded)
add_subdirectory(server)
# Doxygen documentation target
find_package(Doxygen)

if(DOXYGEN_FOUND)
    set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating HTML documentation with Doxygen"
        VERBATIM
    )
else()
    message(STATUS "Doxygen not found. The 'docs' target will not be available.")
endif()
if(ENABLE_COVERAGE AND GCOVR_EXECUTABLE)
    add_custom_target(coverage
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/coverage
        COMMAND ${GCOVR_EXECUTABLE}
            --root ${CMAKE_SOURCE_DIR}
            --filter ${CMAKE_SOURCE_DIR}/embedded
            --filter ${CMAKE_SOURCE_DIR}/server
            --exclude ${CMAKE_BINARY_DIR}/_deps
            --exclude '.*/CMakeFiles/.*'
            --html-details
            --output ${CMAKE_BINARY_DIR}/coverage/index.html
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running tests and generating HTML coverage report with gcovr"
        VERBATIM
    )
endif()
