
LOCAL_PATH:= $(call my-dir)

CFLAGS := -Wpointer-arith -Wwrite-strings -Wunused -Winline \
 -Wnested-externs -Wmissing-declarations -Wmissing-prototypes -Wno-long-long \
 -Wfloat-equal -Wno-multichar -Wsign-compare -Wno-format-nonliteral \
 -Wendif-labels -Wstrict-prototypes -Wdeclaration-after-statement \
 -Wno-system-headers -DHAVE_CONFIG_H
#-m32

#ifeq ($(TARGET_ARCH_ABI),mips64)   
 # CFLAGS+=-O3 -Os
 #endif   
 ########################################

 #using libssl.so
include $(CLEAR_VARS) 
LOCAL_MODULE := libssl
LOCAL_SRC_FILES := ${LOCAL_PATH}/../..//openssl-android/obj/local/${TARGET_ARCH_ABI}/libssl.so 
include $(PREBUILT_SHARED_LIBRARY)

#using libcrypto.so
include $(CLEAR_VARS) 
LOCAL_MODULE := libcrypto
LOCAL_SRC_FILES :=${LOCAL_PATH}/../..//openssl-android/obj/local/${TARGET_ARCH_ABI}/libcrypto.so 
include $(PREBUILT_SHARED_LIBRARY)
 
 
#########################
 
 
include $(CLEAR_VARS)
include $(LOCAL_PATH)/lib/Makefile.inc

LOCAL_SRC_FILES := $(addprefix lib/,$(CSOURCES))
LOCAL_CFLAGS += $(CFLAGS)
#LOCAL_CPPFLAGS += $(CFLAGS)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/ $(LOCAL_PATH)/lib \
${LOCAL_PATH}/../../openssl-android/include ${LOCAL_PATH}/../../openssl-android/crypto #####openssl##########

LOCAL_COPY_HEADERS_TO := libcurl
LOCAL_COPY_HEADERS := $(addprefix include/curl/,$(HHEADERS))


LOCAL_SHARED_LIBRARIES:= libssl  libcrypto  libz  ###########共享库##########
LOCAL_MODULE:= libcurl

include $(BUILD_SHARED_LIBRARY)

