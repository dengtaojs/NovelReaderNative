
# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

cmake_minimum_required(VERSION 3.22.1)
project("novelreadernative")

set(CMAKE_CXX_STANDARD 20)
set(ARM64_ANDROID $ENV{ARM64_ANDROID})

# INCLUDE Folders
include_directories(
    ${ARM64_ANDROID}/include
    ${CMAKE_SOURCE_DIR}/include
)

# Files
file(GLOB LIBRARY_FILES
    ${ARM64_ANDROID}/lib/libuchardet.a
    ${ARM64_ANDROID}/lib/libced.a
    ${ARM64_ANDROID}/lib/libicuuc.a
)

file(GLOB HEADER_FILES
    ${CMAKE_SOURCE_DIR}/include/CharsetDetector.h
    ${CMAKE_SOURCE_DIR}/include/UnicodeConverter.h
)

file(GLOB SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/source/CharsetDetector.cpp
    ${CMAKE_SOURCE_DIR}/source/UnicodeConverter.cpp
)

file(GLOB JNI_FILES
    ${CMAKE_SOURCE_DIR}/jni/NativeHelper.cpp
)

# define target
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
