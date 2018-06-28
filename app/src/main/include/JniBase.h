//
// Created by Administrator on 2018/6/22.
//

#ifndef PICTUREJNI_JNIBASE_H
#define PICTUREJNI_JNIBASE_H

#include <jni.h>
#include <android/log.h>

#define JNI_LOG_TAG "JNILOG"
#define JNI_LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, JNI_LOG_TAG, __VA_ARGS__)
#define JNI_LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, JNI_LOG_TAG, __VA_ARGS__)
#define JNI_LOGI(...) __android_log_print(ANDROID_LOG_INFO, JNI_LOG_TAG, __VA_ARGS__)
#define JNI_LOGW(...) __android_log_print(ANDROID_LOG_WARN, JNI_LOG_TAG, __VA_ARGS__)
#define JNI_LOGE(...) __android_log_print(ANDROID_LOG_ERROR, JNI_LOG_TAG, __VA_ARGS__)

#define JNI_VALUE(x) #x

#endif //PICTUREJNI_JNIBASE_H
