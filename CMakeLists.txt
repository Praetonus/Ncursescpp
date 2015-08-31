cmake_minimum_required(VERSION 2.8)

project(ncursescpp)

set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

option(BUILD_SHARED "Build the library as a shared object." ON)

if(BUILD_SHARED)
    set(LIBRARY_TYPE SHARED)
else(BUILD_SHARED)
    set(LIBRARY_TYPE STATIC)
endif(BUILD_SHARED)

file(GLOB_RECURSE source_files src/*.cpp)
file(GLOB_RECURSE headers src/*.hpp)

add_library(ncursescpp ${LIBRARY_TYPE} ${source_files})

install(TARGETS ncursescpp DESTINATION lib)
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ncursescpp/)
