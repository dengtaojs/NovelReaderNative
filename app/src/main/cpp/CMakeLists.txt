
# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

cmake_minimum_required(VERSION 3.22.1)
project("novelreadernative")

set(CMAKE_CXX_STANDARD 20)
set(VCPKG_ANDROID $ENV{VCPKG_ANDROID})

include_directories(
    ${VCPKG_ANDROID}/include
    ${CMAKE_SOURCE_DIR}/include
)

file(GLOB LIBRARY_FILES
    ${VCPKG_ANDROID}/lib/libuchardet.a
    ${VCPKG_ANDROID}/lib/libicudata.a
    ${VCPKG_ANDROID}/lib/libicuuc.a
)

file(GLOB HEADER_FILES
    ${CMAKE_SOURCE_DIR}/include/TextTools.h
    ${CMAKE_SOURCE_DIR}/include/U16Decoder.h
)

file(GLOB SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/source/TextTools.cpp
    ${CMAKE_SOURCE_DIR}/source/U16Decoder.cpp
)

file(GLOB JNI_FILES
    ${CMAKE_SOURCE_DIR}/jni/NativeHelper.cpp
)

add_library(${CMAKE_PROJECT_NAME} SHARED
    ${HEADER_FILES}
    ${SOURCE_FILES}
    ${JNI_FILES}
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    ${LIBRARY_FILES}
    android
    log
)
