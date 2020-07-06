cmake_minimum_required(VERSION 3.2)

project(ip_filter)

set(HEADERS)

set(SOURCES
    ip_filter.cpp
)

add_executable(ip_filter ${HEADERS} ${SOURCES})

set_target_properties(ip_filter PROPERTIES
    CXX_STANDART 14
    CXX_STANDART_REQUIRED ON
)