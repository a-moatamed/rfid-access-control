# ==============================================================================
# Project:      [rfid-access-control/server]
# Description:  CMake configuration for the authentication server library.
#               This library provides the core functionality for the RFID access 
#               control system's authentication server.
# Author:       [Abdelrahman Abomosa / TEAM 15 - UPB]
# ==============================================================================

# create a static library from the source file
add_library(auth_server_lib STATIC src/AuthServer.cpp) 

# specify the include directories for the library
target_include_directories(auth_server_lib PUBLIC include) 
