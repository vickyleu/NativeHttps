# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.4.1)

###################################################################################
###################################################################################
###################################LibJsonCpp########################################
###################################################################################
###################################################################################
###################################################################################
#设置cmakelist libcurl的目标路径
#######查找cpp目录下的所有源文件并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(jni/libjsoncpp  DIR_JSON_LIB_SRCS)
#增加Cpp动态共享库
add_library (jsonlib SHARED ${DIR_JSON_LIB_SRCS})

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

add_library(jcrypto  SHARED  IMPORTED )
#增加so文件动态共享库，${ANDROID_ABI}表示so文件的ABI类型的路径
set_target_properties(jcrypto PROPERTIES IMPORTED_LOCATION
${libcurl_DIR}/libs/${ANDROID_ABI}/libcrypto.so)

add_library(jssl SHARED   IMPORTED )
#增加so文件动态共享库，${ANDROID_ABI}表示so文件的ABI类型的路径
set_target_properties(jssl PROPERTIES IMPORTED_LOCATION
${libcurl_DIR}/libs/${ANDROID_ABI}/libssl.so)

add_library(jcurl SHARED   IMPORTED )
#增加so文件动态共享库，${ANDROID_ABI}表示so文件的ABI类型的路径
set_target_properties(jcurl PROPERTIES IMPORTED_LOCATION
${libcurl_DIR}/libs/${ANDROID_ABI}/libcurl.so)


###################################################################################
###################################################################################
###################################################################################
###################################################################################




message(STATUS "Source files libssl.so path is: " ${libcurl_DIR}/libs/${ANDROID_ABI}/libssl.so)



#######查找cpp目录下的所有源文件并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(src/main/cpp  DIR_LIB_SRCS)
aux_source_directory(src/main/cpp/pkg  DIR_LIB_SRCS_PKG)
message(STATUS "妈卖批: " ${DIR_LIB_SRCS})





#增加Cpp动态共享库
find_library(log-lib  log )
add_library (native SHARED ${DIR_LIB_SRCS} ${DIR_LIB_SRCS_PKG})


#增加include包含的路径所有头文件
include_directories(${libcurl_DIR}/)

#生成链接动态库
target_link_libraries(native
${log-lib}
 jcrypto
 jssl
 jcurl
 jsonlib
 )

