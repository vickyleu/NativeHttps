# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_C_COMPILER clang++)
#add_compile_options(-std=c++1y -pedantic)
aux_source_directory(./ DIR_JSON_LIB_SRCS)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DJSON_IS_AMALGAMATION ")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -DJSON_IS_AMALGAMATION ")


#增加Cpp动态共享库
add_library(jsonlib STATIC ${DIR_JSON_LIB_SRCS})


