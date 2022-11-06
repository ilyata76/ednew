cmake_minimum_required(VERSION 3.0)

set (PROJECT_POCO pococos)

project(${PROJECT_POCO} VERSION 0.1.0)

set(ENTRYPOINT_POCO
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

set (HEADERS_POCO
    #
)

set (SOURCES_POCO
    #
)

add_subdirectory(
    ${CMAKE_SOURCE_DIR}/src/poco
)

add_executable( 
    main
    ${ENTRYPOINT_POCO} ${HEADERS_POCO} ${SOURCES_POCO}
) 

target_include_directories(main PUBLIC src/poco-include)
target_link_libraries(main Poco::Foundation Poco::Net Poco::Util)