/* include/curl/curlbuild.h.  Generated from curlbuild.h.in by configure.  */
#ifndef __CURL_CURLBUILD_H
#define __CURL_CURLBUILD_H
/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2012, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
/*




 "CURL_SIZEOF_LONG definition is missing!"
there is a way for it .
change the curlbuild.h at line number 162 add like this,if you are arm32 platform.
//todo 修复方法备份
//----------------------------------------------add
#    define CURL_SIZEOF_LONG           4 //
#    define CURL_TYPEOF_CURL_OFF_T     long long //
#    define CURL_FORMAT_CURL_OFF_T     "lld"
#    define CURL_FORMAT_CURL_OFF_TU    "llu"
#    define CURL_FORMAT_OFF_T          "%lld"
#    define CURL_SIZEOF_CURL_OFF_T     8
#    define CURL_SUFFIX_CURL_OFF_T     LL
#    define CURL_SUFFIX_CURL_OFF_TU    ULL
#  define CURL_TYPEOF_CURL_SOCKLEN_T unsigned int
#  define CURL_SIZEOF_CURL_SOCKLEN_T 4
//#define __SYMBIAN32__


 */
/* ================================================================ */
/*               NOTES FOR CONFIGURE CAPABLE SYSTEMS                */
/* ================================================================ */

/*
 * NOTE 1:
 * -------
 *
 * Nothing in this file is intended to be modified or adjusted by the
 * curl library user nor by the curl library builder.
 *
 * If you think that something actually needs to be changed, adjusted
 * or fixed in this file, then, report it on the libcurl development
 * mailing list: https://cool.haxx.se/mailman/listinfo/curl-library/
 *
 * This header file shall only export symbols which are 'curl' or 'CURL'
 * prefixed, otherwise public name space would be polluted.
 *
 * NOTE 2:
 * -------
 *
 * Right now you might be staring at file include/curl/curlbuild.h.in or
 * at file include/curl/curlbuild.h, this is due to the following reason:
 *
 * On systems capable of running the configure script, the configure process
 * will overwrite the distributed include/curl/curlbuild.h file with one that
 * is suitable and specific to the library being configured and built, which
 * is generated from the include/curl/curlbuild.h.in template file.
 *
 */

/* ================================================================ */
/*  DEFINITION OF THESE SYMBOLS SHALL NOT TAKE PLACE ANYWHERE ELSE  */
/* ================================================================ */

#ifdef CURL_SIZEOF_LONG
#error "CURL_SIZEOF_LONG shall not be defined except in curlbuild.h"
Error Compilation_aborted_CURL_SIZEOF_LONG_already_defined
#endif

#ifdef CURL_TYPEOF_CURL_SOCKLEN_T
#error "CURL_TYPEOF_CURL_SOCKLEN_T shall not be defined except in curlbuild.h"
Error Compilation_aborted_CURL_TYPEOF_CURL_SOCKLEN_T_already_defined
#endif

#ifdef CURL_SIZEOF_CURL_SOCKLEN_T
#error "CURL_SIZEOF_CURL_SOCKLEN_T shall not be defined except in curlbuild.h"
Error Compilation_aborted_CURL_SIZEOF_CURL_SOCKLEN_T_already_defined
#endif

#ifdef CURL_TYPEOF_CURL_OFF_T
#error "CURL_TYPEOF_CURL_OFF_T shall not be defined except in curlbuild.h"
Error Compilation_aborted_CURL_TYPEOF_CURL_OFF_T_already_defined
#endif

#ifdef CURL_FORMAT_CURL_OFF_T
#error "CURL_FORMAT_CURL_OFF_T shall not be defined except in curlbuild.h"
Error Compilation_aborted_CURL_FORMAT_CURL_OFF_T_already_defined
#endif

#ifdef CURL_FORMAT_CURL_OFF_TU
#error "CURL_FORMAT_CURL_OFF_TU shall not be defined except in curlbuild.h"
Error Compilation_aborted_CURL_FORMAT_CURL_OFF_TU_already_defined
#endif

#ifdef CURL_FORMAT_OFF_T
#error "CURL_FORMAT_OFF_T shall not be defined except in curlbuild.h"
Error Compilation_aborted_CURL_FORMAT_OFF_T_already_defined
#endif

#ifdef CURL_SIZEOF_CURL_OFF_T
#error "CURL_SIZEOF_CURL_OFF_T shall not be defined except in curlbuild.h"
Error Compilation_aborted_CURL_SIZEOF_CURL_OFF_T_already_defined
#endif

#ifdef CURL_SUFFIX_CURL_OFF_T
#error "CURL_SUFFIX_CURL_OFF_T shall not be defined except in curlbuild.h"
Error Compilation_aborted_CURL_SUFFIX_CURL_OFF_T_already_defined
#endif

#ifdef CURL_SUFFIX_CURL_OFF_TU
#error "CURL_SUFFIX_CURL_OFF_TU shall not be defined except in curlbuild.h"
Error Compilation_aborted_CURL_SUFFIX_CURL_OFF_TU_already_defined
#endif

/* ================================================================ */
/*  EXTERNAL INTERFACE SETTINGS FOR CONFIGURE CAPABLE SYSTEMS ONLY  */
/* ================================================================ */

/* Configure process defines this to 1 when it finds out that system  */
/* header file ws2tcpip.h must be included by the external interface. */
/* #undef CURL_PULL_WS2TCPIP_H */
#ifdef CURL_PULL_WS2TCPIP_H
#  ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#  endif
#  include <windows.h>
#  include <winsock2.h>
#  include <ws2tcpip.h>
#endif

/* Configure process defines this to 1 when it finds out that system   */
/* header file sys/types.h must be included by the external interface. */
#define CURL_PULL_SYS_TYPES_H 1
#ifdef CURL_PULL_SYS_TYPES_H

#  include <sys/types.h>

#endif

/* Configure process defines this to 1 when it finds out that system */
/* header file stdint.h must be included by the external interface.  */
/* #undef CURL_PULL_STDINT_H */
#ifdef CURL_PULL_STDINT_H
#  include <stdint.h>
#endif

/* Configure process defines this to 1 when it finds out that system  */
/* header file inttypes.h must be included by the external interface. */
/* #undef CURL_PULL_INTTYPES_H */
#ifdef CURL_PULL_INTTYPES_H
#  include <inttypes.h>
#endif

/* Configure process defines this to 1 when it finds out that system    */
/* header file sys/socket.h must be included by the external interface. */
#define CURL_PULL_SYS_SOCKET_H 1
#ifdef CURL_PULL_SYS_SOCKET_H

#  include <sys/socket.h>

#endif

/* Configure process defines this to 1 when it finds out that system  */
/* header file sys/poll.h must be included by the external interface. */
/* #undef CURL_PULL_SYS_POLL_H */
#ifdef CURL_PULL_SYS_POLL_H
#  include <sys/poll.h>
#endif



/* Integral data type used for curl_socklen_t. */
#ifdef __LP64__
#define CURL_TYPEOF_CURL_SOCKLEN_T socklen_t
#else
#define CURL_TYPEOF_CURL_SOCKLEN_T unsigned int  //todo fix 64 bit system build 32 bit source
#endif

/* The size of `curl_socklen_t', as computed by sizeof. */
#define CURL_SIZEOF_CURL_SOCKLEN_T 4

/* Data type definition of curl_socklen_t. */
typedef CURL_TYPEOF_CURL_SOCKLEN_T curl_socklen_t;

/* Signed integral data type used for curl_off_t. */
#ifdef __LP64__
#define CURL_TYPEOF_CURL_OFF_T long
#else
#define CURL_TYPEOF_CURL_OFF_T int64_t  //todo fix 64 bit system build 32 bit source
#endif

/* Data type definition of curl_off_t. */
typedef CURL_TYPEOF_CURL_OFF_T curl_off_t;

/* curl_off_t formatting string directive without "%" conversion specifier. */
#ifdef __LP64__
#define CURL_FORMAT_CURL_OFF_T "ld"
#else
#define CURL_FORMAT_CURL_OFF_T "lld"  //todo fix 64 bit system build 32 bit source
#endif
/* unsigned curl_off_t formatting string without "%" conversion specifier. */
#ifdef __LP64__
#define CURL_FORMAT_CURL_OFF_TU "lu"
#else
#define CURL_FORMAT_CURL_OFF_TU "llu"   //todo fix 64 bit system build 32 bit source
#endif
/* curl_off_t formatting string directive with "%" conversion specifier. */
#ifdef __LP64__
#define CURL_FORMAT_OFF_T "%ld"
#else
#define CURL_FORMAT_OFF_T "%lld"   //todo fix 64 bit system build 32 bit source
#endif
/* The size of `long', as computed by sizeof. */
#ifdef __LP64__
#define CURL_SIZEOF_LONG 8
#else
#define CURL_SIZEOF_LONG 4  //todo fix 64 bit system build 32 bit source
#endif

/* The size of `curl_off_t', as computed by sizeof. */
#ifdef __LP64__
#define CURL_SIZEOF_CURL_OFF_T 8
#else
#define CURL_SIZEOF_CURL_OFF_T 8  //todo fix 64 bit system build 32 bit source
#endif
/* curl_off_t constant suffix. */
#ifdef __LP64__
#define CURL_SUFFIX_CURL_OFF_T L
#else
#define CURL_SUFFIX_CURL_OFF_T LL //todo fix 64 bit system build 32 bit source
#endif



/* unsigned curl_off_t constant suffix. */
#ifdef __LP64__
#define CURL_SUFFIX_CURL_OFF_TU UL
#else
#define CURL_SUFFIX_CURL_OFF_TU ULL //todo fix 64 bit system build 32 bit source
#endif


#endif /* __CURL_CURLBUILD_H */
