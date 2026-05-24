
// create the library
add_library(auth_server_lib STATIC src/AuthServer.cpp) 

// specify the include directory for the library
target_include_directories(auth_server_lib PUBLIC include) 
