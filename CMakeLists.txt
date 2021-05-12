cmake_minimum_required(VERSION 3.8)
project(Zia)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")
set(RUNTIME_OUTPUT_DIRECTORY build)
set(CMAKE_CXX_STANDARD 17)

if(UNIX)
    add_definitions("-O3")
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

include(build/conanbuildinfo.cmake)
include(build/conan_paths.cmake)
conan_basic_setup(KEEP_RPATHS)
include_directories(${CMAKE_INCLUDE_PATH})

find_package(Boost REQUIRED)

find_package(PkgConfig)

find_path(CRITERION_INCLUDE_DIR criterion/criterion.h
          PATH_SUFFIXES criterion)

find_library(CRITERION_LIBRARY NAMES criterion libcriterion)

set(CRITERION_LIBRARIES ${CRITERION_LIBRARY})
set(CRITERION_INCLUDE_DIRS ${CRITERION_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Criterion DEFAULT_MSG
                                  CRITERION_LIBRARY CRITERION_INCLUDE_DIR)

mark_as_advanced(CRITERION_INCLUDE_DIR CRITERION_LIBRARY)

include_directories(
    CRITERION_INCLUDE_DIRS 

    src/common
    src/thread
    src/request
    src/library_loader
)
include_directories(CRITERION_INCLUDE_DIRS)

set(MAIN
    src/main.cpp    
)

set(SRCS_COMMON
    src/common/Configuration.cpp
)

include_directories(
    src/common/include
    src/thread/include
    src/request/include
    src/library_loader/include
    src/server/Network/include
    src/server/
)

set(SRCS_SERVER
    src/server/ZiaCore.cpp
    src/server/Network/src/TcpConnection.cpp
    src/server/SignalHandler.cpp
    )

set(SRCS_TEST
    tests/unit_tests.cpp
)

add_executable(zia ${MAIN} ${SRCS_COMMON} ${SRCS_SERVER})



if(WIN32)
	target_link_libraries(zia libboost_system libboost_serialization Threads::Threads)
elseif (UNIX)
	target_link_libraries(zia boost_system boost_serialization Threads::Threads dl)
    target_link_libraries(zia boost_system Threads::Threads boost_serialization)
endif()