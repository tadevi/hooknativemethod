//
// VirtualApp Native Project
//

#ifndef NDK_CORE_H
#define NDK_CORE_H

#include <jni.h>
#include <stdlib.h>

#include <android/log.h>

#define TAG "V++"

#define ALOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG ,__VA_ARGS__)
#define ALOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG ,__VA_ARGS__)
#define ALOGW(...) __android_log_print(ANDROID_LOG_WARN, TAG ,__VA_ARGS__)
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG ,__VA_ARGS__)

#define HOOK_SYMBOL(handle, func) hook_function(handle, #func, (void*) new_##func, (void**) &orig_##func)

#define HOOK_DEF(ret, func, ...) \
  ret (*orig_##func)(__VA_ARGS__); \
  ret new_##func(__VA_ARGS__)

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved);
JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* vm, void* reserved);


#endif //NDK_CORE_H
