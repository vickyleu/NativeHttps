# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_COMPILER clang++)
add_compile_options(-std=c++1y -pedantic)
#######查找cpp目录下的所有源文件并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(./ DIR_LIB_SRCS)
aux_source_directory(./pkg DIR_LIB_SRCS_PKG)
aux_source_directory(./protobuf PB_SRC)
message(STATUS "妈卖批: " ${DIR_LIB_SRCS})


#增加Cpp动态共享库
find_library(log-lib log)
add_library(native SHARED
        ${DIR_LIB_SRCS}
        ${DIR_LIB_SRCS_PKG}
        ${PB_SRC}
        )

target_include_directories(native PUBLIC ../../../jni/libprotobuf)
target_include_directories(native PUBLIC ../../../jni/libopenssl/include)
target_include_directories(native PUBLIC ../../../jni/libjsoncpp)
target_include_directories(native PUBLIC ../../../jni/libcurl/include)

#生成链接动态库
target_link_libraries(native
        ${log-lib}
        ssl
        crypto
        #curl
        protobuf
        jsonlib
        zbar
        )

add_definitions(-Wall)

#自定义命令 因为AndroidStudio漏洞的原因,将预编译的动态库复制到预编译目录中,等待打包到apk中
add_custom_command(TARGET native POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${libcurl_DIR}/libs/${ANDROID_ABI}" $<TARGET_FILE_DIR:native>)
add_custom_command(TARGET native POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${libcurl_DIR}/../libzbar/libs/${ANDROID_ABI}" $<TARGET_FILE_DIR:native>)
#add_custom_command(TARGET native POST_BUILD
#       COMMAND ${CMAKE_COMMAND} -E copy_directory "${libprotobuf_DIR}/libs/${ANDROID_ABI}" $<TARGET_FILE_DIR:native>)


