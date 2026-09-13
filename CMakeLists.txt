cmake_minimum_required(VERSION 3.17)
project(CursorGuard)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/lib)

add_executable(CursorGuard
    source/main.cpp
    source/CursorLock/CursorLock.cpp
    source/Monitor/Monitor.cpp
)

target_link_libraries(CursorGuard PRIVATE
    user32
)