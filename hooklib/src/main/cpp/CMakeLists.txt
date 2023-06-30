cmake_minimum_required(VERSION 3.4.1)

set(LIBRARY_NAME "hooklib")

add_definitions("-DCORE_SO_NAME=\"lib${LIBRARY_NAME}.so\"")

include_directories(.)
set(CMAKE_ANDROID_STL_TYPE c++_static)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


add_library(
        ${LIBRARY_NAME}
        SHARED
        jni/jni.cpp
        substrate/hde64.c
        substrate/SubstrateDebug.cpp
        substrate/SubstrateHook.cpp
        substrate/SubstratePosixMemory.cpp
        substrate/And64InlineHook.cpp
)

target_link_libraries(
        ${LIBRARY_NAME}
        android
        log)

if (${CMAKE_ANDROID_ARCH_ABI} STREQUAL "armeabi-v7a")
    add_custom_command(TARGET ${LIBRARY_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${LIBRARY_NAME}> $<TARGET_FILE_DIR:${LIBRARY_NAME}>/../arm64-v8a/lib${LIBRARY_NAME}_ext.so
            )
    if(EXISTS $<TARGET_FILE_DIR:${LIBRARY_NAME}>/../arm64-v8a/lib${LIBRARY_NAME}.so)
        add_custom_command(TARGET ${LIBRARY_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:${LIBRARY_NAME}>/../arm64-v8a/lib${LIBRARY_NAME}.so $<TARGET_FILE_DIR:${LIBRARY_NAME}>/lib${LIBRARY_NAME}_ext.so
                )
    endif()
endif()

if (${CMAKE_ANDROID_ARCH_ABI} STREQUAL "arm64-v8a")
    add_custom_command(TARGET ${LIBRARY_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${LIBRARY_NAME}> $<TARGET_FILE_DIR:${LIBRARY_NAME}>/../armeabi-v7a/lib${LIBRARY_NAME}_ext.so
            )
    if(EXISTS $<TARGET_FILE_DIR:${LIBRARY_NAME}>/../armeabi-v7a/lib${LIBRARY_NAME}.so)
        add_custom_command(TARGET ${LIBRARY_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:${LIBRARY_NAME}>/../armeabi-v7a/lib${LIBRARY_NAME}.so $<TARGET_FILE_DIR:${LIBRARY_NAME}>/lib${LIBRARY_NAME}_ext.so
                )
    endif()
endif()