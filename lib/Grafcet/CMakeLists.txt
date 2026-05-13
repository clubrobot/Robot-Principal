cmake_minimum_required(VERSION 4.2)
project(grafcet)

set(GRAFCET_MAX_NODE_PARENTS 10 CACHE STRING "Max parents per node")
set(GRAFCET_MAX_NODE_CHILDREN 10 CACHE STRING "Max children per node")
set(GRAFCET_MAX_QUEUE_SIZE 10 CACHE STRING "Max queue size")
add_library(grafcet STATIC src/StateMachine.cpp)
target_include_directories(grafcet PUBLIC include)
target_compile_features(grafcet PUBLIC cxx_std_23)

configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/include/GrafcetConfig.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/generated/GrafcetConfig.h
        @ONLY
)

target_include_directories(grafcet PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR}/generated
)
