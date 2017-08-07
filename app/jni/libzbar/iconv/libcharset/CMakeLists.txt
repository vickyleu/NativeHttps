cmake_minimum_required(VERSION 3.4.1)

add_library(charset STATIC
        lib/localcharset.c)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_CONFIG_H -DBUILDING_LIBCHARSET -DIN_LIBRARY -DLIBDIR=\"\"")
target_include_directories(charset PUBLIC include)


