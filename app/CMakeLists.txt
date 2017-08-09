# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html
cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_BUILD_TYPE Debug)

#SET(GLOBAL BUILD_SSL ON)
#SET(GLOBAL BUILD_CURL OFF)
#SET(GLOBAL BUILD_JSONCPP OFF)
#SET(GLOBAL BUILD_PROTOBUF OFF)
#SET(GLOBAL BUILD_ZBAR OFF)
#SET(GLOBAL BUILD_NATIVE OFF)
#
#if (${BUILD_SSL})
#    message(STATUS "妈卖批: BUILD_SSL")

#endif ()


add_subdirectory(jni/libopenssl)
add_subdirectory(jni/libcurl)
add_subdirectory(jni/libjsoncpp)
add_subdirectory(jni/libprotobuf)
add_subdirectory(jni/libzbar)
add_subdirectory(src/main/cpp)


