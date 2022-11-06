cmake_minimum_required(VERSION 3.16)

project(ed_gtest)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/libs/googletest)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/libs/benchmark)

add_executable(${PROJECT_NAME}
            ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
)

target_link_libraries(${PROJECT_NAME}
            gtest
            gmock
            benchmark::benchmark
)