cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

project (Get)
set(CMAKE_BUILD_TYPE Release)

if(UNIX)
    add_definitions("-O3")
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Zia-Docs/include/zia
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Zia-Docs/include/zia/module
)
add_library(Get SHARED Get.cpp)