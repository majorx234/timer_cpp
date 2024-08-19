cmake_minimum_required(VERSION 3.16)

project(timer
  DESCRIPTION "cpp implementation of a timer object"
  VERSION 0.1.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set( PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include )

find_package( Threads )

set(TIMER_HEADERS
  include/timer.hpp
)
set(TIMER_SOURCES
  src/timer.cpp
)

add_library(timer SHARED)
target_sources(timer
 PRIVATE
    ${TIMER_SOURCES}
    ${TIMER_HEADERS}
)
target_include_directories(timer SYSTEM
 PRIVATE
  include
  ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(timer
 Threads::Threads
)
set_target_properties(timer PROPERTIES PUBLIC_HEADER "${TIMER_HEADERS}")

