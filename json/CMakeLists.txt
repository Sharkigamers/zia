cmake_minimum_required(VERSION 3.8)
project (Test)
set(CMAKE_CXX_STANDARD 17)

if(UNIX)
    add_definitions("-g3")
endif()

set(CMAKE_BUILD_TYPE Debug)

find_package(Boost REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Zia-Docs/include/zia
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Zia-Docs/include/zia/module
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/request/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/common/include/
)

add_executable(Test main.cpp)