#***************************************************************************
#                                  _   _ ____  _
#  Project                     ___| | | |  _ \| |
#                             / __| | | | |_) | |
#                            | (__| |_| |  _ <| |___
#                             \___|\___/|_| \_\_____|
#
# Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
#
# This software is licensed as described in the file COPYING, which
# you should have received as part of this distribution. The terms
# are also available at https://curl.haxx.se/docs/copyright.html.
#
# You may opt to use, copy, modify, merge, publish, distribute and/or sell
# copies of the Software, and permit persons to whom the Software is
# furnished to do so, under the terms of the COPYING file.
#
# This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
# KIND, either express or implied.
#
###########################################################################
# cURL/libcurl CMake script
# by Tetetest and Sukender (Benoit Neil)

cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11
-Wpointer-arith
-Wwrite-strings
-Wunused
-Winline
-Wnested-externs
-Wmissing-declarations
-Wmissing-prototypes
-Wno-long-long
-Wfloat-equal
-Wno-multichar
-Wsign-compare
-Wno-format-nonliteral
-Wendif-labels
-Wstrict-prototypes
-Wdeclaration-after-statement
-Wno-system-headers
-DHAVE_CONFIG_H
")#-m32

if ($(ANDROID_ABI) STREQUAL "mips64")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3  -Os")
endif ()

set(LIB_VTLS_CFILES
        lib/vtls/openssl.c
        lib/vtls/gtls.c
        lib/vtls/vtls.c
        lib/vtls/nss.c
        lib/vtls/polarssl.c
        lib/vtls/polarssl_threadlock.c
        lib/vtls/axtls.c
        lib/vtls/cyassl.c
        lib/vtls/schannel.c
        lib/vtls/darwinssl.c
        lib/vtls/gskit.c
        lib/vtls/mbedtls.c)

set(LIB_VTLS_HFILES
        lib/vtls/openssl.h
        lib/vtls/vtls.h
        lib/vtls/gtls.h
        lib/vtls/nssg.h
        lib/vtls/polarssl.h
        lib/vtls/polarssl_threadlock.h
        lib/vtls/axtls.h
        lib/vtls/cyassl.h
        lib/vtls/schannel.h
        lib/vtls/darwinssl.h
        lib/vtls/gskit.h
        lib/vtls/mbedtls.h)

set(LIB_CFILES
        lib/file.c
        lib/timeval.c
        lib/base64.c
        lib/hostip.c
        lib/progress.c
        lib/formdata.c
        lib/cookie.c
        lib/http.c
        lib/sendf.c
        lib/ftp.c
        lib/url.c
        lib/dict.c
        lib/if2ip.c
        lib/speedcheck.c
        lib/ldap.c
        lib/version.c
        lib/getenv.c
        lib/escape.c
        lib/mprintf.c
        lib/telnet.c
        lib/netrc.c
        lib/getinfo.c
        lib/transfer.c
        lib/strequal.c
        lib/easy.c
        lib/security.c
        lib/curl_fnmatch.c
        lib/fileinfo.c
        lib/ftplistparser.c
        lib/wildcard.c
        lib/krb5.c
        lib/memdebug.c
        lib/http_chunks.c
        lib/strtok.c
        lib/connect.c
        lib/llist.c
        lib/hash.c
        lib/multi.c
        lib/content_encoding.c
        lib/share.c
        lib/http_digest.c
        lib/md4.c
        lib/md5.c
        lib/http_negotiate.c
        lib/inet_pton.c
        lib/strtoofft.c
        lib/strerror.c
        lib/amigaos.c
        lib/hostasyn.c
        lib/hostip4.c
        lib/hostip6.c
        lib/hostsyn.c
        lib/inet_ntop.c
        lib/parsedate.c
        lib/select.c
        lib/tftp.c
        lib/splay.c
        lib/strdup.c
        lib/socks.c
        lib/ssh.c
        lib/rawstr.c
        lib/curl_addrinfo.c
        lib/socks_gssapi.c
        lib/socks_sspi.c
        lib/curl_sspi.c
        lib/slist.c
        lib/nonblock.c
        lib/curl_memrchr.c
        lib/imap.c
        lib/pop3.c
        lib/smtp.c
        lib/pingpong.c
        lib/rtsp.c
        lib/curl_threads.c
        lib/warnless.c
        lib/hmac.c
        lib/curl_rtmp.c
        lib/openldap.c
        lib/curl_gethostname.c
        lib/gopher.c
        lib/idn_win32.c
        lib/http_negotiate_sspi.c
        lib/http_proxy.c
        lib/non-ascii.c
        lib/asyn-ares.c
        lib/asyn-thread.c
        lib/curl_gssapi.c
        lib/curl_ntlm.c
        lib/curl_ntlm_wb.c
        lib/curl_ntlm_core.c
        lib/curl_ntlm_msgs.c
        lib/curl_sasl.c
        lib/curl_multibyte.c
        lib/hostcheck.c
        lib/conncache.c
        lib/pipeline.c
        lib/dotdot.c
        lib/x509asn1.c
        lib/http2.c
        lib/curl_sasl_sspi.c
        lib/smb.c
        lib/curl_sasl_gssapi.c
        lib/curl_endian.c
        lib/curl_des.c)

set(LIB_HFILES
        lib/arpa_telnet.h
        lib/netrc.h
        lib/file.h
        lib/curl_config.h
        lib/timeval.h
        lib/hostip.h
        lib/progress.h
        lib/formdata.h
        lib/cookie.h
        lib/http.h
        lib/sendf.h
        lib/ftp.h
        lib/url.h
        lib/dict.h
        lib/if2ip.h
        lib/speedcheck.h
        lib/urldata.h
        lib/curl_ldap.h
        lib/escape.h
        lib/telnet.h
        lib/getinfo.h
        lib/strequal.h
        lib/curl_sec.h
        lib/memdebug.h
        lib/http_chunks.h
        lib/curl_fnmatch.h
        lib/wildcard.h
        lib/fileinfo.h
        lib/ftplistparser.h
        lib/strtok.h
        lib/connect.h
        lib/llist.h
        lib/hash.h
        lib/content_encoding.h
        lib/share.h
        lib/curl_md4.h
        lib/curl_md5.h
        lib/http_digest.h
        lib/http_negotiate.h
        lib/inet_pton.h
        lib/amigaos.h
        lib/strtoofft.h
        lib/strerror.h
        lib/inet_ntop.h
        lib/curlx.h
        lib/curl_memory.h
        lib/curl_setup.h
        lib/transfer.h
        lib/select.h
        lib/easyif.h
        lib/multiif.h
        lib/parsedate.h
        lib/tftp.h
        lib/sockaddr.h
        lib/splay.h
        lib/strdup.h
        lib/socks.h
        lib/ssh.h
        lib/curl_base64.h
        lib/rawstr.h
        lib/curl_addrinfo.h
        lib/curl_sspi.h
        lib/slist.h
        lib/nonblock.h
        lib/curl_memrchr.h
        lib/imap.h
        lib/pop3.h
        lib/smtp.h
        lib/pingpong.h
        lib/rtsp.h
        lib/curl_threads.h
        lib/warnless.h
        lib/curl_hmac.h
        lib/curl_rtmp.h
        lib/curl_gethostname.h
        lib/gopher.h
        lib/http_proxy.h
        lib/non-ascii.h
        lib/asyn.h
        lib/curl_ntlm.h
        lib/curl_gssapi.h
        lib/curl_ntlm_wb.h
        lib/curl_ntlm_core.h
        lib/curl_ntlm_msgs.h
        lib/curl_sasl.h
        lib/curl_multibyte.h
        lib/hostcheck.h
        lib/conncache.h
        lib/curl_setup_once.h
        lib/multihandle.h
        lib/setup-vms.h
        lib/pipeline.h
        lib/dotdot.h
        lib/x509asn1.h
        lib/http2.h
        lib/sigpipe.h
        lib/smb.h
        lib/curl_endian.h
        lib/curl_des.h
        lib/curl_printf.h)
set(LIB_RCFILES lib/libcurl.rc)

set(CSOURCES ${LIB_CFILES} ${LIB_VTLS_CFILES})
set(HHEADERS ${LIB_HFILES} ${LIB_VTLS_HFILES})

#configure_file(lib/curl_config.h.cmake lib/curl_config.h)
#configure_file(lib/curlbuild.h.cmake lib/curlbuild.h)


find_library(libz C:/Develop/Android/SDK/ndk-bundle/platforms/android-24/${ANDROID_ABI}/usr/lib/libz.so)

add_library(curl SHARED
                  ${CSOURCES})

target_include_directories(curl PUBLIC
        ./include
       ${HHEADERS}
        ../libopenssl/include
        ../libopenssl/crypto)

#增加Cpp动态共享库
find_library(log-lib log)
#生成链接动态库
target_link_libraries(curl
        ${log-lib}
        libz
        ssl
        crypto
        )


