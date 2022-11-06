cmake_minimum_required (VERSION 3.0)

set (PG pgwebapi)

##########

project (${PG} VERSION 0.0.1)

option(ENABLE_DATA_POSTGRESQL "data postgres" ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_PREFIX_PATH "E:/PSQL") # postgres

##########

set (ENTRYPOINT_PG
	"src/main.cpp"
) 

set (SOURCES_PG
    #
)

set (HEADERS_PG
    #
)

set (RESOURCES_PG
    #
)

###########

add_subdirectory(
    "${CMAKE_CURRENT_LIST_DIR}/src/poco-lib"
)

add_subdirectory(
    "${CMAKE_CURRENT_LIST_DIR}/src/pretty-tables-lib"
)

add_subdirectory(
    "${CMAKE_CURRENT_LIST_DIR}/src/exceptio-lib"
)

########### 

add_executable(
    ${PG} 
    ${ENTRYPOINT_PG} 
    ${HEADERS_PG} 
    ${SOURCES_PG} 
    ${RESOURCES_PG}
)

    target_include_directories(
        ${PG}
            PRIVATE
                "${CMAKE_CURRENT_LIST_DIR}/include"
    )

# Линкуем POCO
    target_link_libraries(
        ${PG} 
        Poco::Foundation 
        Poco::Net 
        Poco::Util
        Poco::Data
        Poco::DataPostgreSQL
    ) 
    
# Линкуем tia
    target_link_libraries(
        ${PG} 
        exceptio
        prettytables
    )

###########




