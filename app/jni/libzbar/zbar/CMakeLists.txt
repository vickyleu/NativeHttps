cmake_minimum_required(VERSION 3.4.1)

add_library(zbar STATIC
        zbarjni.c
        img_scanner.c
        decoder.c
        config.h
        image.c
        symbol.c
        convert.c
        config.c
        scanner.c
        error.c
        refcnt.c
        video.c
        video/null.c
        decoder/code128.c
        decoder/code39.c
        decoder/code93.c
        decoder/codabar.c
        decoder/databar.c
        decoder/ean.c
        decoder/i25.c
        decoder/qr_finder.c
        qrcode/bch15_5.c
        qrcode/binarize.c
        qrcode/isaac.c
        qrcode/qrdec.c
        qrcode/qrdectxt.c
        qrcode/rs.c
        qrcode/util.c)
set(CMAKE_CXX_FLAGS "liconv  ${CMAKE_CXX_FLAGS}  -std=c++11 -DANDROID_STL=gnustl_static")
target_include_directories(zbar PUBLIC
        ../include
        ./
        ../iconv/include)

find_library(log-lib log)
target_link_libraries(zbar iconv ${log-lib})
