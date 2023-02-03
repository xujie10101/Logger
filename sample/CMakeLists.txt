project(Logger-sample VERSION 1.0)

if(${CMAKE_GENERATOR} MATCHES "Visual Studio*")
    #在Visual Studio生成器（即VS工程）下，会在EXECUTABLE_OUTPUT_PATH、EXECUTABLE_OUTPUT_PATH后面自动加一个${CMAKE_BUILD_TYPE}
    SET(EXECUTABLE_OUTPUT_PATH  ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}) #可执行文件输出目录
    set(LIBRARY_OUTPUT_PATH  ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE})    #库文件输出目录
else()
    #在其他环境下，不会动，原来是什么就是什么
    SET(EXECUTABLE_OUTPUT_PATH  ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE})
    set(LIBRARY_OUTPUT_PATH  ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE})
endif()

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(
        ${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include
)
message(STATUS " ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/Logger-sdk.lib" )
target_link_libraries(
        ${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/Logger-sdk.lib
)

if(${CMAKE_GENERATOR} MATCHES "Visual Studio*")
    #在Visual Studio生成器（即VS工程）下，会在EXECUTABLE_OUTPUT_PATH、EXECUTABLE_OUTPUT_PATH后面自动加一个${CMAKE_BUILD_TYPE}
    set_target_properties(${PROJECT_NAME}
            PROPERTIES
            LINKER_LANGUAGE CXX
            ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
            LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
            )
else()
    #在其他环境下，不会动，原来是什么就是什么
    set_target_properties(${PROJECT_NAME}
            PROPERTIES
            LINKER_LANGUAGE CXX
            ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}
            LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}
            )
endif()