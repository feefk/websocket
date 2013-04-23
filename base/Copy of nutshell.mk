LOCAL_PATH:= $(call my-dir)

local_c_includes_ := \
	externals/utilsbase

local_src_files_ := \
	event_recorder_stubs.cc \
	file_descriptor_shuffle.cc \
	linux_util.cc \
	md5.cc \
	message_pump_libevent.cc \
	metrics/field_trial.cc \
	sync_socket_posix.cc \
	third_party/dmg_fp/g_fmt.cc \
	third_party/dmg_fp/dtoa_wrapper.cc \
	third_party/icu/icu_utf.cc \
	third_party/nspr/prtime.cc \
	allocator/allocator_extension.cc \
	at_exit.cc \
	atomicops_internals_x86_gcc.cc \
	base_paths.cc \
	base_paths_posix.cc \
	base64.cc \
	bind_helpers.cc \
	build_time.cc \
	callback_internal.cc \
	command_line.cc \
	cpu.cc \
	debug/alias.cc \
	debug/debugger.cc \
	debug/debugger_posix.cc \
	debug/profiler.cc \
	debug/stack_trace.cc \
	debug/stack_trace_posix.cc \
	debug/trace_event.cc \
	debug/trace_event_impl.cc \
	environment.cc \
	file_path.cc \
	file_util.cc \
	file_util_linux.cc \
	file_util_posix.cc \
	file_util_proxy.cc \
	files/file_path_watcher.cc \
	files/file_path_watcher_linux.cc \
	global_descriptors_posix.cc \
	guid.cc \
	guid_posix.cc \
	hi_res_timer_manager_posix.cc \
	json/json_file_value_serializer.cc \
	json/json_parser.cc \
	json/json_reader.cc \
	json/json_string_value_serializer.cc \
	json/json_writer.cc \
	json/string_escape.cc \
	lazy_instance.cc \
	location.cc \
	logging.cc \
	memory/aligned_memory.cc \
	memory/ref_counted.cc \
	memory/ref_counted_memory.cc \
	memory/singleton.cc \
	memory/weak_ptr.cc \
	message_loop.cc \
	message_loop_proxy.cc \
	message_loop_proxy_impl.cc \
	message_pump.cc \
	message_pump_default.cc \
	metrics/bucket_ranges.cc \
	metrics/histogram.cc \
	metrics/histogram_base.cc \
	metrics/histogram_snapshot_manager.cc \
	metrics/statistics_recorder.cc \
	metrics/stats_counters.cc \
	metrics/stats_table.cc \
	native_library_posix.cc \
	path_service.cc \
	pending_task.cc \
	pickle.cc \
	platform_file.cc \
	platform_file_posix.cc \
	posix/unix_domain_socket.cc \
	process_linux.cc \
	process_posix.cc \
	process_util.cc \
	process_util_linux.cc \
	process_util_posix.cc \
	profiler/scoped_profile.cc \
	profiler/alternate_timer.cc \
	profiler/tracked_time.cc \
	property_bag.cc \
	rand_util.cc \
	rand_util_posix.cc \
	run_loop.cc \
	safe_strerror_posix.cc \
	scoped_native_library.cc \
	scoped_temp_dir.cc \
	sequenced_task_runner.cc \
	sha1_portable.cc \
	shared_memory_posix.cc \
	string_number_conversions.cc \
	string_piece.cc \
	string_split.cc \
	string_util.cc \
	string16.cc \
	stringprintf.cc \
	supports_user_data.cc \
	synchronization/cancellation_flag.cc \
	synchronization/condition_variable_posix.cc \
	synchronization/lock.cc \
	synchronization/lock_impl_posix.cc \
	synchronization/waitable_event_posix.cc \
	synchronization/waitable_event_watcher_posix.cc \
	system_monitor/system_monitor.cc \
	system_monitor/system_monitor_posix.cc \
	sys_info_linux.cc \
	sys_info_posix.cc \
	sys_string_conversions_posix.cc \
	task_runner.cc \
	thread_task_runner_handle.cc \
	threading/non_thread_safe_impl.cc \
	threading/platform_thread_posix.cc \
	threading/post_task_and_reply_impl.cc \
	threading/sequenced_worker_pool.cc \
	threading/simple_thread.cc \
	threading/thread.cc \
	threading/thread_checker_impl.cc \
	threading/thread_collision_warner.cc \
	threading/thread_local_posix.cc \
	threading/thread_local_storage_posix.cc \
	threading/thread_restrictions.cc \
	threading/watchdog.cc \
	threading/worker_pool.cc \
	threading/worker_pool_posix.cc \
	time.cc \
	time_posix.cc \
	timer.cc \
	tracked_objects.cc \
	tracking_info.cc \
	utf_offset_string_conversions.cc \
	utf_string_conversion_utils.cc \
	utf_string_conversions.cc \
	values.cc \
	value_conversions.cc \
	version.cc \
	vlog.cc
	

#######################################
# target static library
include $(CLEAR_VARS)
include $(LOCAL_PATH)/../nutshell-config.mk

LOCAL_CPP_EXTENSION := .cc
LOCAL_SRC_FILES += $(local_src_files_)
LOCAL_C_INCLUDES += $(local_c_includes_)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= libbase_static
include $(BUILD_STATIC_LIBRARY)

#######################################
# target shared library
include $(CLEAR_VARS)
include $(LOCAL_PATH)/../nutshell-config.mk

ifneq ($(TARGET_ARCH),x86)
#LOCAL_NDK_VERSION := 5
#LOCAL_SDK_VERSION := 9
endif
LOCAL_SRC_FILES += $(local_src_files_)
LOCAL_C_INCLUDES += $(local_c_includes_)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= libbase
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
