cmake_minimum_required(VERSION 3.8)
project (phpCgi)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Release)

include(build/conanbuildinfo.cmake)
include(build/conan_paths.cmake)
conan_basic_setup(KEEP_RPATHS)
include_directories(${CMAKE_INCLUDE_PATH})

if(UNIX)
    add_definitions("-O3")
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Zia-Docs/include/zia
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Zia-Docs/include/zia/module
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/request/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/common/include/
)
add_library(phpCgi SHARED phpCgi.cpp)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

target_link_libraries(phpCgi ${CONAN_LIBS})
