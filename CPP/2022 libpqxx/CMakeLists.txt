cmake_minimum_required(VERSION 3.18)

project(POSTGRES)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set (ENTRYPOINT
    ${CMAKE_CURRENT_LIST_DIR}/sources/main.cpp
)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)


# set(PostgreSQL_LIBRARY "E:/PSQL/lib")
# set(PostgreSQL_INCLUDE_DIR "E:/PSQL/include")
set(CMAKE_PREFIX_PATH "E:/PSQL")
add_subdirectory(sources/libpqxx)
add_subdirectory(sources/pretty-tables)

add_executable(executable ${ENTRYPOINT})
target_include_directories(executable PUBLIC ${CMAKE_CURRENT_LIST_DIR}/sources/libpqxx/include)
target_link_libraries(executable pqxx)

target_include_directories(executable PUBLIC ${CMAKE_CURRENT_LIST_DIR}/sources/pretty-tables/include)
target_link_libraries(executable prettytables)