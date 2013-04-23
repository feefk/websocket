LOCAL_PATH:= $(call my-dir)

local_c_includes_ := \
	externals/utilsbase

local_src_files_ := \
          test/ws_server.cc
          
           
           

#######################################
# target share library
include $(CLEAR_VARS)
include $(LOCAL_PATH)/../nutshell-config.mk

LOCAL_CPP_EXTENSION := .cc
LOCAL_SRC_FILES += $(local_src_files_)
LOCAL_C_INCLUDES += $(local_c_includes_)
ifneq ($(TARGET_ARCH),x86)
LOCAL_C_INCLUDES += externals/zlib
endif 
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= ws_server
LOCAL_LDFLAGS := -lz
LOCAL_SHARED_LIBRARIES := libWebBase libWebIPC libwebserver
include $(BUILD_EXECUTABLE)





