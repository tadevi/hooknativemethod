#include "../substrate/SubstrateHook.h"
#include <sys/ptrace.h>
#include <unistd.h>
#include "jni.h"
#include <dlfcn.h>
#include <time.h>

HOOK_DEF(void, fsync, int fd) {
    clock_t begin = clock();
    orig_fsync(fd);
    clock_t end = clock();
    ALOGD("### FSYNC DONE!: %ld", (end - begin) / 1000);
}

static inline void
hook_function(void *handle, const char *symbol, void *new_func, void **old_func) {
    void *addr = dlsym(handle, symbol);
    if (addr == nullptr) {
        ALOGE("Not found symbol : %s", symbol);
        return;
    }
    MSHookFunction(addr, new_func, old_func);
}

void hook() {
    void *handle = dlopen("libc.so", RTLD_NOW);
    if (handle) {
        HOOK_SYMBOL(handle, fsync);
        dlclose(handle);
    }
}


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *_vm, void *) {
    hook();
    return JNI_VERSION_1_6;
}