//
// Created by heima on 2018/6/1.
//

#ifndef JNITEST_ANDROID_LOG_H
#define JNITEST_ANDROID_LOG_H
#include <android/log.h>

#define TAG "HM"
// __VA_ARGS__ 代表 ...的可变参数
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG,  __VA_ARGS__);
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG,  __VA_ARGS__);
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG,  __VA_ARGS__);
#endif //JNITEST_ANDROID_LOG_H
