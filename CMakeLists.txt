cmake_minimum_required (VERSION 3.8)
project("PointSetPartition")

if(UNIX) 
    message(STATUS ">>> Linux")
	set(CMAKE_BUILD_TYPE Release)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
elseif(WIN32)
    message(STATUS ">>> Windows")
    set(CMAKE_CXX_FLAGS_RELEASE "-Ox")
endif()


set(BUILD_STATIC_LIBS ON)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

link_directories (${PROJECT_BINARY_DIR})

include_directories("include/Differential_Evolution")
include_directories("include/Geometry")

add_subdirectory("tests")

add_executable("PointSetPartition" "PointSetPartition.cpp")