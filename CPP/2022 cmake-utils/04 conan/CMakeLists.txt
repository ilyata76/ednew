cmake_minimum_required(VERSION 3.24)

project(conan_test)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(
    ${CMAKE_PROJECT_NAME} 
        main.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME} ${CONAN_LIBS})
    