cmake_minimum_required(VERSION 3.8)
project (SSL)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Release)

if(UNIX)
    add_definitions("-O3")
endif()

include(build/conanbuildinfo.cmake)
include(build/conan_paths.cmake)
conan_basic_setup(KEEP_RPATHS)
include_directories(${CMAKE_INCLUDE_PATH})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Zia-Docs/include/zia
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Zia-Docs/include/zia/module
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/request/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/common/include/
)
add_library(SSL SHARED SSL.cpp)

target_link_libraries(SSL ${CONAN_LIBS})
