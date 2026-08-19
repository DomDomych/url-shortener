cmake_minimum_required(VERSION 3.10)

project(url_shortener)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(url_shortener
    example/main.cpp
    src/url_shortener.cpp
)

target_include_directories(url_shortener PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)