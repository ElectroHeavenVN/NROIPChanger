//
//  Logger.h
//
//  Created by MJ (Ruit) on 1/1/19.
//

#ifndef Logger_h
#define Logger_h

#include <jni.h>
#include <android/log.h>

#define TAG "NROIPChanger"

#define LOGF(...) ((void)__android_log_print(ANDROID_LOG_FATAL, TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN,  TAG, __VA_ARGS__))
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO,  TAG, __VA_ARGS__))
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__))
#define LOGV(...) ((void)__android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__))

#endif /* Logger_h */
