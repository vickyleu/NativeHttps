cmake_minimum_required(VERSION 3.4.1)

add_subdirectory(libcharset)

add_library(iconv STATIC lib/iconv.c  libcharset/lib/localcharset.c  lib/relocatable.c)
set(CMAKE_CXX_FLAGS "-Wno-multichar -D_ANDROID  -std=c++11 -DANDROID_STL=gnustl_static -DLIBDIR='c' -DBUILDING_LIBICONV -DBUILDING_LIBCHARSET
-DIN_LIBRARY ${CMAKE_CXX_FLAGS}")

target_include_directories(iconv PUBLIC
        include
        srclib
        libcharset
        libcharset/include)


