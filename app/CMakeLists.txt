# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html
cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_BUILD_TYPE Debug)
add_subdirectory(jni/libopenssl)
add_subdirectory(jni/libcurl)
add_subdirectory(jni/libjsoncpp)
add_subdirectory(jni/libprotobuf)
add_subdirectory(jni/libzbar)
add_subdirectory(src/main/cpp)




