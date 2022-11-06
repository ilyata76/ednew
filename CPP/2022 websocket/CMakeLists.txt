cmake_minimum_required(VERSION 3.0)

set (PROJECT_WS WEBSOCKETS)

project(${PROJECT_WS} VERSION 0.1.0)

set(ENTRYPOINT_WS
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

set (HEADERS_WS
    #
)

set (SOURCES_WS
    #
)

if(WIN32) 
    set (HEADERS_WS ${HEADERS_WS} ${CMAKE_SOURCE_DIR}/src/winsocks.hpp ${CMAKE_SOURCE_DIR}/src/winlogic.hpp)
    set (SOURCES_WS ${SOURCES_WS} ${CMAKE_SOURCE_DIR}/src/winsocks.cpp ${CMAKE_SOURCE_DIR}/src/winlogic.cpp)
endif()

add_executable(
    main    
    ${ENTRYPOINT_WS} ${HEADERS_WS} ${SOURCES_WS}
) 

if(WIN32)
    target_link_libraries(main
        Ws2_32
    )
endif()
