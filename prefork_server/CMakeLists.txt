cmake_minimum_required(VERSION 3.16)
project(static_server)

set(CMAKE_CXX_STANDARD 20)

include_directories(config server client parser structs handler)

add_executable(static_server main.cpp
        config/Config.cpp server/Server.cpp
        client/Client.cpp parser/Parser.cpp)