cmake_minimum_required(VERSION 3.0.0)
project(pdp11 VERSION 0.1.0)

SET(CMAKE_CXX_FLAGS "-std=c++17")

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache) # Less useful to do it for linking, see edit2
endif(CCACHE_FOUND)

set(SOURCES
    main.cpp
    unibus.cpp
    lsi11.cpp)

add_executable(pdp11 main.cpp ${SOURCES})