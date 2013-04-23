LOCAL_PATH:= $(call my-dir)

local_c_includes_ := \
	externals/utilsbase

local_src_files_ := \
	base/event_recorder_stubs.cc \
	base/file_descriptor_shuffle.cc \
	base/linux_util.cc \
	base/base_switches.cc \
	base/md5.cc \
    base/message_pump_libevent.cc \
    base/metrics/field_trial.cc \
    base/sync_socket_posix.cc \
    base/third_party/dmg_fp/g_fmt.cc \
    base/third_party/dmg_fp/dtoa_wrapper.cc \
    base/third_party/icu/icu_utf.cc \
    base/third_party/nspr/prtime.cc \
    base/at_exit.cc \
    base/atomicops_internals_x86_gcc.cc \
    base/base_paths.cc \
    base/base_paths_posix.cc \
    base/base64.cc \
    base/bind_helpers.cc \
    base/build_time.cc \
    base/callback_internal.cc \
    base/command_line.cc \
    base/cpu.cc \
    base/debug/alias.cc \
    base/debug/debugger.cc \
    base/debug/debugger_posix.cc \
    base/debug/profiler.cc \
    base/debug/stack_trace.cc \
    base/debug/stack_trace_posix.cc \
    base/debug/trace_event.cc \
    base/debug/trace_event_impl.cc \
    base/environment.cc \
    base/file_path.cc \
    base/file_util.cc \
    base/file_util_linux.cc \
    base/file_util_posix.cc \
    base/file_util_proxy.cc \
    base/files/file_path_watcher.cc \
    base/files/file_path_watcher_linux.cc \
    base/global_descriptors_posix.cc \
    base/guid.cc \
    base/guid_posix.cc \
    base/hi_res_timer_manager_posix.cc \
    base/json/json_file_value_serializer.cc \
    base/json/json_parser.cc \
    base/json/json_reader.cc \
    base/json/json_string_value_serializer.cc \
    base/json/json_writer.cc \
    base/json/string_escape.cc \
    base/lazy_instance.cc \
    base/location.cc \
    base/logging.cc \
    base/memory/aligned_memory.cc \
    base/memory/ref_counted.cc \
    base/memory/ref_counted_memory.cc \
    base/memory/singleton.cc \
    base/memory/weak_ptr.cc \
    base/message_loop.cc \
    base/message_loop_proxy.cc \
    base/message_loop_proxy_impl.cc \
    base/message_pump.cc \
    base/message_pump_proxy.cc \
    base/message_pump_default.cc \
    base/metrics/bucket_ranges.cc \
    base/metrics/histogram.cc \
    base/metrics/histogram_base.cc \
    base/metrics/histogram_snapshot_manager.cc \
    base/metrics/statistics_recorder.cc \
    base/metrics/stats_counters.cc \
    base/metrics/stats_table.cc \
    base/native_library_posix.cc \
    base/path_service.cc \
    base/pending_task.cc \
    base/pickle.cc \
    base/platform_file.cc \
    base/platform_file_posix.cc \
    base/posix/unix_domain_socket.cc \
    base/process_linux.cc \
    base/process_posix.cc \
    base/process_util.cc \
    base/process_util_linux.cc \
    base/process_util_posix.cc \
    base/profiler/scoped_profile.cc \
    base/profiler/alternate_timer.cc \
    base/profiler/tracked_time.cc \
    base/property_bag.cc \
    base/rand_util.cc \
    base/rand_util_posix.cc \
    base/run_loop.cc \
    base/safe_strerror_posix.cc \
    base/scoped_native_library.cc \
    base/scoped_temp_dir.cc \
    base/sequenced_task_runner.cc \
    base/sha1_portable.cc \
    base/shared_memory_posix.cc \
    base/string_number_conversions.cc \
    base/string_piece.cc \
    base/string_split.cc \
    base/string_util.cc \
    base/string16.cc \
    base/stringprintf.cc \
    base/supports_user_data.cc \
    base/synchronization/cancellation_flag.cc \
    base/synchronization/condition_variable_posix.cc \
    base/synchronization/lock.cc \
    base/synchronization/lock_impl_posix.cc \
    base/synchronization/waitable_event_posix.cc \
    base/synchronization/waitable_event_watcher_posix.cc \
    base/system_monitor/system_monitor.cc \
    base/system_monitor/system_monitor_posix.cc \
    base/sys_info_linux.cc \
    base/sys_info_posix.cc \
    base/sys_string_conversions_posix.cc \
    base/task_runner.cc \
    base/thread_task_runner_handle.cc \
    base/threading/non_thread_safe_impl.cc \
    base/threading/platform_thread_posix.cc \
    base/threading/post_task_and_reply_impl.cc \
    base/threading/sequenced_worker_pool.cc \
    base/threading/simple_thread.cc \
    base/threading/thread.cc \
    base/threading/thread_checker_impl.cc \
    base/threading/thread_collision_warner.cc \
    base/threading/thread_local_posix.cc \
    base/threading/thread_local_storage_posix.cc \
    base/threading/thread_restrictions.cc \
    base/threading/watchdog.cc \
    base/threading/worker_pool.cc \
    base/threading/worker_pool_posix.cc \
    base/time.cc \
    base/time_posix.cc \
    base/timer.cc \
    base/tracked_objects.cc \
    base/tracking_info.cc \
    base/utf_offset_string_conversions.cc \
    base/utf_string_conversion_utils.cc \
    base/utf_string_conversions.cc \
    base/values.cc \
    base/value_conversions.cc \
    base/version.cc \
    base/vlog.cc \
    base/third_party/dynamic_annotations/dynamic_annotations.c \
    third_party/modp_b64/modp_b64.cc
    
#base/allocator/allocator_extension.cc 
	

#######################################
# target static library
include $(CLEAR_VARS)
include $(LOCAL_PATH)/nutshell-config.mk

LOCAL_CPP_EXTENSION := .cc
LOCAL_SRC_FILES += $(local_src_files_)
LOCAL_C_INCLUDES += $(local_c_includes_)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= libWebBase_static
include $(BUILD_STATIC_LIBRARY)

#######################################
# target shared library
include $(CLEAR_VARS)
include $(LOCAL_PATH)/nutshell-config.mk

ifneq ($(TARGET_ARCH),x86)
#LOCAL_NDK_VERSION := 5
#LOCAL_SDK_VERSION := 9
endif
LOCAL_CPP_EXTENSION := .cc
LOCAL_SRC_FILES += $(local_src_files_)
LOCAL_C_INCLUDES += $(local_c_includes_)
LOCAL_MODULE_TAGS := optional
LOCAL_SHARED_LIBRARIES := libevent
#LOCAL_SHARED_LIBRARIES := libevnet_static
LOCAL_MODULE:= libWebBase
LOCAL_LDFLAGS := -lrt -lpthread -ldl
include $(BUILD_SHARED_LIBRARY)

# ssltest
#include $(CLEAR_VARS)
#include $(LOCAL_PATH)/../nutshell-config.mk
#LOCAL_SRC_FILES:= ssltest.c
#LOCAL_C_INCLUDES += $(local_c_includes)
#LOCAL_SHARED_LIBRARIES := libssl libcrypto
#LOCAL_MODULE:= ssltest
#LOCAL_MODULE_TAGS := optional
#LOCAL_LDFLAGS := -ldl
#include $(BUILD_EXECUTABLE)
