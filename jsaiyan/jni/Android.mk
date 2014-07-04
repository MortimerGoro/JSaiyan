LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := jsaiyan
LOCAL_LDLIBS := \
	-llog \
	-lc
LOCAL_SRC_FILES := \
	jsaiyan.cpp
include $(BUILD_SHARED_LIBRARY)
