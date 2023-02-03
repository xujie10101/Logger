
PROJECT(Logger-sdk VERSION 1.0)


file(GLOB SOURCES ./*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_include_directories(
        ${PROJECT_NAME} PUBLIC
        ${CMAKE_SOURCE_DIR}/include
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
#————————————————
#版权声明：本文为CSDN博主「geodoer」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
#原文链接：https://blog.csdn.net/summer_dew/article/details/121935540




