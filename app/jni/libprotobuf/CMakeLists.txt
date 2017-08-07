
cmake_minimum_required(VERSION 3.4.1)


set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_COMPILER clang++)
add_compile_options(-std=c++1y -pedantic)

set(PROTOBUF_SRC
        google/protobuf/descriptor_database.cc
        google/protobuf/descriptor.cc
        google/protobuf/arena.cc
        google/protobuf/stubs/stringpiece.cc
        google/protobuf/stubs/int128.cc
        google/protobuf/descriptor.pb.cc
        google/protobuf/dynamic_message.cc
        google/protobuf/extension_set_heavy.cc
        google/protobuf/extension_set.cc
        google/protobuf/generated_message_reflection.cc
        google/protobuf/generated_message_util.cc
        google/protobuf/io/coded_stream.cc
        google/protobuf/io/gzip_stream.cc
        google/protobuf/io/printer.cc
        google/protobuf/io/strtod.cc
        google/protobuf/io/tokenizer.cc
        google/protobuf/io/zero_copy_stream_impl_lite.cc
        google/protobuf/io/zero_copy_stream_impl.cc
        google/protobuf/io/zero_copy_stream.cc
        google/protobuf/message_lite.cc
        google/protobuf/message.cc
        google/protobuf/reflection_ops.cc
        google/protobuf/repeated_field.cc
        google/protobuf/stubs/common.cc
        google/protobuf/stubs/status.cc
        google/protobuf/stubs/once.cc
        google/protobuf/stubs/stringprintf.cc
        google/protobuf/stubs/structurally_valid.cc
        google/protobuf/stubs/strutil.cc
        google/protobuf/stubs/substitute.cc
        google/protobuf/text_format.cc
        google/protobuf/unknown_field_set.cc
        google/protobuf/wire_format_lite.cc
        google/protobuf/wire_format.cc
        google/protobuf/stubs/atomicops_internals_x86_gcc.cc
        )


#if ($(ANDROID_ABI) STREQUAL "x86")
#    set(PROTOBUF_SRC
#            google/protobuf/stubs/atomicops_internals_x86_gcc.cc)
#    message(STATUS "protobuf啊啊: " ${PROTOBUF_SRC}/)
#elseif ($(ANDROID_ABI) STREQUAL "x86_64")
#    set(PROTOBUF_SRC
#             google/protobuf/stubs/atomicops_internals_x86_gcc.cc)
#    message(STATUS "protobuf啊啊: " ${PROTOBUF_SRC}/)
#endif ()

add_library(protobuf STATIC ${PROTOBUF_SRC})
find_library(z C:/Develop/Android/SDK/ndk-bundle/platforms/android-24/${ANDROID_ABI}/usr/lib/libz.so)

##增加gcc警告和调试标志
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lz -DHAVE_PTHREAD=1 -DGOOGLE_PROTOBUF_NO_RTTI=1")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -lz -lm  -DHAVE_PTHREAD=1 -DGOOGLE_PROTOBUF_NO_RTTI=1")
include_directories(./)
