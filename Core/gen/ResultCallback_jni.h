
// This file is autogenerated by
//     /Users/dli/Documents/lynx/lynx-native/lynx/build/jni_generator.py
// For
//     com/lynx/core/ResultCallback

#ifndef com_lynx_core_ResultCallback_JNI
#define com_lynx_core_ResultCallback_JNI

#include <jni.h>

#include "base/android/android_jni.h"

// Step 1: forward declarations.
namespace {
const char kResultCallbackClassPath[] = "com/lynx/core/ResultCallback";
// Leaking this jclass as we cannot use LazyInstance from some threads.
jclass g_ResultCallback_clazz = NULL;
#define ResultCallback_clazz(env) g_ResultCallback_clazz

}  // namespace

// Step 2: method stubs.

static intptr_t g_ResultCallback_onReceiveResult = 0;
static void Java_ResultCallback_onReceiveResult(JNIEnv* env, jobject obj,
    jobject result) {
  /* Must call RegisterNativesImpl()  */
  //CHECK_CLAZZ(env, obj,
  //    ResultCallback_clazz(env));
  jmethodID method_id =
      base::android::GetMethod(
      env, ResultCallback_clazz(env),
      base::android::INSTANCE_METHOD,
      "onReceiveResult",

"("
"Ljava/lang/Object;"
")"
"V",
      &g_ResultCallback_onReceiveResult);

     env->CallVoidMethod(obj,
          method_id, result);
  base::android::CheckException(env);

}

// Step 3: RegisterNatives.

static bool RegisterNativesImpl(JNIEnv* env) {

  g_ResultCallback_clazz = reinterpret_cast<jclass>(env->NewGlobalRef(
      base::android::GetClass(env, kResultCallbackClassPath).Get()));

  return true;
}

#endif  // com_lynx_core_ResultCallback_JNI
