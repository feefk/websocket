LOCAL_PATH:= $(call my-dir)

local_c_includes_ := \
	externals/utilsbase

local_src_files_ := \
           net/server/http_connection.cc \
           net/server/http_server_request_info.cc \
           net/server/http_server.cc \
           net/server/web_socket.cc \
           net/base/stream_listen_socket.cc \
           net/base/backoff_entry.cc \
           net/base/io_buffer.cc \
           net/base/tcp_listen_socket.cc \
           net/base/net_errors.cc \
           net/server/socket_set_nonblocking.cc \
           net/server/js_extension_handler.cc \
           net/server/js_extension_handler_websocket_impl.cc
           
           

#######################################
# target share library
include $(CLEAR_VARS)
include $(LOCAL_PATH)/nutshell-config.mk

LOCAL_CPP_EXTENSION := .cc
LOCAL_SRC_FILES += $(local_src_files_)
LOCAL_C_INCLUDES += $(local_c_includes_)
ifneq ($(TARGET_ARCH),x86)
LOCAL_C_INCLUDES += externals/zlib
endif 
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= libwebserver
LOCAL_LDFLAGS := -lz
LOCAL_SHARED_LIBRARIES := libWebBase
LOCAL_CFLAGS += -DLWS_LIBRARY_VERSION='"1.2"' -DLWS_BUILD_HASH='"ccaf140"' -DLWS_NO_EXTENSIONS
include $(BUILD_SHARED_LIBRARY)

#######################################
# target share library
include $(CLEAR_VARS)
include $(LOCAL_PATH)/nutshell-config.mk

LOCAL_CPP_EXTENSION := .cc
LOCAL_SRC_FILES += $(local_src_files_)
LOCAL_C_INCLUDES += $(local_c_includes_)
ifneq ($(TARGET_ARCH),x86)
LOCAL_C_INCLUDES += externals/zlib
endif 
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= libwebserver_static
LOCAL_LDFLAGS := -lz
LOCAL_CFLAGS += -DLWS_LIBRARY_VERSION='"1.2"' -DLWS_BUILD_HASH='"ccaf140"' -DLWS_NO_EXTENSIONS
include $(BUILD_STATIC_LIBRARY)


# target excutable 
include $(CLEAR_VARS)
include $(LOCAL_PATH)/nutshell-config.mk

LOCAL_CPP_EXTENSION := .cc
LOCAL_SRC_FILES += net/test/js_extension_test.cc
LOCAL_C_INCLUDES += $(local_c_includes_)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := js_extension_test
LOCAL_SHARED_LIBRARIES := libwebserver libWebBase
include $(BUILD_EXECUTABLE)
