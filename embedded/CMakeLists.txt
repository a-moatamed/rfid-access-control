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