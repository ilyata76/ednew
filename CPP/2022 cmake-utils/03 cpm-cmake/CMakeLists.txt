cmake_minimum_required(VERSION 3.24)

project(cpm_test)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# для корректной работы нужно скачать .cmake скрипт
include(cmake/CPM.cmake)

CPMAddPackage(
  NAME benchmark
  GITHUB_REPOSITORY google/benchmark
  VERSION 1.5.2
  OPTIONS "BENCHMARK_ENABLE_TESTING Off" # "... Off" "... On" "... Off"
)

if(benchmark_ADDED)
  # enable c++11 to avoid compilation errors
  set_target_properties(benchmark PROPERTIES CXX_STANDARD 11)
endif()

add_executable(
    ${CMAKE_PROJECT_NAME} 
        main.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME} benchmark)
    