cmake_minimum_required(VERSION 3.21)
project(smallEstore)

set(CMAKE_CXX_STANDARD 23)

add_executable(smallEstore init.cpp networkIO.cpp networkIO.h serverLog.h serverLog.cpp database.h database.cpp settings.h init.h threadPool.h base64.cpp base64.h)
