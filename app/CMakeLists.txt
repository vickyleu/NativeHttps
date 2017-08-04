# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.4.1)


set(CMAKE_BUILD_TYPE Debug)

###################################################################################
###################################################################################
###################################LibJsonCpp########################################
###################################################################################
###################################################################################
###################################################################################
#设置cmakelist libcurl的目标路径
#######查找cpp目录下的所有源文件并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(jni/libjsoncpp DIR_JSON_LIB_SRCS)
#增加include包含的路径所有头文件

#增加Cpp动态共享库
add_library(jsonlib SHARED ${DIR_JSON_LIB_SRCS})
###################################################################################
###################################################################################
###################################################################################
###################################################################################


###################################################################################
###################################################################################
###################################LibCurl########################################
###################################################################################
###################################################################################
###################################################################################
#设置cmakelist libcurl的目标路径
set(libcurl_DIR ${CMAKE_SOURCE_DIR}/jni/libcurl)

add_library(jcrypto SHARED IMPORTED)
#增加so文件动态共享库，${ANDROID_ABI}表示so文件的ABI类型的路径
set_target_properties(jcrypto PROPERTIES IMPORTED_LOCATION
        ${libcurl_DIR}/libs/${ANDROID_ABI}/libcrypto.so)

add_library(jssl SHARED IMPORTED)
#增加so文件动态共享库，${ANDROID_ABI}表示so文件的ABI类型的路径
set_target_properties(jssl PROPERTIES IMPORTED_LOCATION
        ${libcurl_DIR}/libs/${ANDROID_ABI}/libssl.so)

add_library(jzbar SHARED IMPORTED)
#增加so文件动态共享库，${ANDROID_ABI}表示so文件的ABI类型的路径
set_target_properties(jzbar PROPERTIES IMPORTED_LOCATION
        ${libcurl_DIR}/../libzbar/libs/${ANDROID_ABI}/libZbar.so)


add_library(jcurl SHARED IMPORTED)
#增加so文件动态共享库，${ANDROID_ABI}表示so文件的ABI类型的路径
set_target_properties(jcurl PROPERTIES IMPORTED_LOCATION
        ${libcurl_DIR}/libs/${ANDROID_ABI}/libcurl.so)


message(STATUS "jcurl path is: " ${libcurl_DIR}/libs/${ANDROID_ABI}/libcurl.so)
###################################################################################
###################################################################################
###################################################################################
###################################################################################


message(STATUS "Source files libssl.so path is: " ${libcurl_DIR}/libs/${ANDROID_ABI}/libssl.so)


#######查找cpp目录下的所有源文件并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(src/main/cpp DIR_LIB_SRCS)
aux_source_directory(src/main/cpp/pkg DIR_LIB_SRCS_PKG)
aux_source_directory(src/main/cpp/protobuf PB_SRC)
message(STATUS "妈卖批: " ${DIR_LIB_SRCS})


#增加Cpp动态共享库
find_library(log-lib log)
add_library(native SHARED
        ${DIR_LIB_SRCS}
        ${DIR_LIB_SRCS_PKG}
        ${PB_SRC}
        )

#增加include包含的路径所有头文件
include_directories(${libcurl_DIR}/)


set(libprotobuf_DIR ${CMAKE_SOURCE_DIR}/jni/libprotobuf)


message(STATUS "妈卖批: " ${libprotobuf_DIR}/include)

set(libprotobuf_SRC
        ${libprotobuf_DIR}/google/protobuf/descriptor_database.cc
        ${libprotobuf_DIR}/google/protobuf/descriptor.cc
        ${libprotobuf_DIR}/google/protobuf/arena.cc
        ${libprotobuf_DIR}/google/protobuf/stubs/stringpiece.cc
        ${libprotobuf_DIR}/google/protobuf/stubs/int128.cc
        ${libprotobuf_DIR}/google/protobuf/descriptor.pb.cc
        ${libprotobuf_DIR}/google/protobuf/dynamic_message.cc
        ${libprotobuf_DIR}/google/protobuf/extension_set_heavy.cc
        ${libprotobuf_DIR}/google/protobuf/extension_set.cc
        ${libprotobuf_DIR}/google/protobuf/generated_message_reflection.cc
        ${libprotobuf_DIR}/google/protobuf/generated_message_util.cc
        ${libprotobuf_DIR}/google/protobuf/io/coded_stream.cc
        ${libprotobuf_DIR}/google/protobuf/io/gzip_stream.cc
        ${libprotobuf_DIR}/google/protobuf/io/printer.cc
        ${libprotobuf_DIR}/google/protobuf/io/strtod.cc
        ${libprotobuf_DIR}/google/protobuf/io/tokenizer.cc
        ${libprotobuf_DIR}/google/protobuf/io/zero_copy_stream_impl_lite.cc
        ${libprotobuf_DIR}/google/protobuf/io/zero_copy_stream_impl.cc
        ${libprotobuf_DIR}/google/protobuf/io/zero_copy_stream.cc
        ${libprotobuf_DIR}/google/protobuf/message_lite.cc
        ${libprotobuf_DIR}/google/protobuf/message.cc
        ${libprotobuf_DIR}/google/protobuf/reflection_ops.cc
        ${libprotobuf_DIR}/google/protobuf/repeated_field.cc
        ${libprotobuf_DIR}/google/protobuf/stubs/common.cc
        ${libprotobuf_DIR}/google/protobuf/stubs/status.cc
        ${libprotobuf_DIR}/google/protobuf/stubs/once.cc
        ${libprotobuf_DIR}/google/protobuf/stubs/stringprintf.cc
        ${libprotobuf_DIR}/google/protobuf/stubs/structurally_valid.cc
        ${libprotobuf_DIR}/google/protobuf/stubs/strutil.cc
        ${libprotobuf_DIR}/google/protobuf/stubs/substitute.cc
        ${libprotobuf_DIR}/google/protobuf/text_format.cc
        ${libprotobuf_DIR}/google/protobuf/unknown_field_set.cc
        ${libprotobuf_DIR}/google/protobuf/wire_format_lite.cc
        ${libprotobuf_DIR}/google/protobuf/wire_format.cc
        ${libprotobuf_DIR}/google/protobuf/stubs/atomicops_internals_x86_gcc.cc
        )


#if ($(ANDROID_ABI) STREQUAL "x86")
#    set(libprotobuf_SRC
#            ${libprotobuf_SRC} +${libprotobuf_DIR}/google/protobuf/stubs/atomicops_internals_x86_gcc.cc)
#    message(STATUS "protobuf啊啊: " ${libprotobuf_SRC}/)
#elseif ($(ANDROID_ABI) STREQUAL "x86_64")
#    set(libprotobuf_SRC
#            ${libprotobuf_SRC} + ${libprotobuf_DIR}/google/protobuf/stubs/atomicops_internals_x86_gcc.cc)
#    message(STATUS "protobuf啊啊: " ${libprotobuf_SRC}/)
#endif ()
#message(STATUS "protobuf啊: " ${libprotobuf_SRC}/)


add_library(jprotobuf STATIC ${libprotobuf_SRC})
find_library(z C:/Develop/Android/SDK/ndk-bundle/platforms/android-24/${ANDROID_ABI}/usr/lib/libz.so)
find_library(m C:/Develop/Android/SDK/ndk-bundle/platforms/android-24/${ANDROID_ABI}/usr/lib/libm.so)


##增加gcc警告和调试标志
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lz -lm -DHAVE_PTHREAD=1 -DGOOGLE_PROTOBUF_NO_RTTI=1")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -lz -lm  -DHAVE_PTHREAD=1 -DGOOGLE_PROTOBUF_NO_RTTI=1")
include_directories(${libprotobuf_DIR}/)


target_link_libraries(jsonlib
        ${log-lib}
        )

target_link_libraries(jprotobuf
        ${log-lib}
        )


#生成链接动态库
target_link_libraries(native
        ${log-lib}
        jssl
        jprotobuf
        jcrypto
        jcurl
        jsonlib
        jzbar
        )

add_definitions(-Wall)

#自定义命令 因为AndroidStudio漏洞的原因,将预编译的动态库复制到预编译目录中,等待打包到apk中
add_custom_command(TARGET native POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${libcurl_DIR}/libs/${ANDROID_ABI}" $<TARGET_FILE_DIR:native>)
add_custom_command(TARGET native POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${libcurl_DIR}/../libzbar/libs/${ANDROID_ABI}" $<TARGET_FILE_DIR:native>)
#add_custom_command(TARGET native POST_BUILD
#       COMMAND ${CMAKE_COMMAND} -E copy_directory "${libprotobuf_DIR}/libs/${ANDROID_ABI}" $<TARGET_FILE_DIR:native>)


