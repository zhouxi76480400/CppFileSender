cmake_minimum_required(VERSION 2.8)
project(CppFileSender)

set(CMAKE_CXX_STANDARD 11)

add_executable(CppFileSender
        main.cpp
        FileSender.cpp
        test/client.cpp test/client.h SocketFile.cpp SocketFile.h SocketFileServer.cpp SocketFileServer.h)