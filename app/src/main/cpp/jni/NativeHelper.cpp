#include <jni.h>
#include "TextTools.h"
#include "U16Decoder.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_dengtao_novelreadernative_jni_NativeHelper_getStringFromByteBuffer(
    JNIEnv *env,
    jobject thiz,
    jobject buffer)
{
    // 1. 获取 buffer 的地址和长度
    const char* data = reinterpret_cast<char*>(env->GetDirectBufferAddress(buffer));
    size_t size = static_cast<size_t>(env->GetDirectBufferCapacity(buffer));

    // 2. 开始转换成 utf16 字符串
    novel::U16Decoder decoder;
    std::u16string result = decoder.toUtf16(data, size);

    // 3. 将 utf16 字符串指针转换成 jchar*
    return env->NewString(
        reinterpret_cast<const jchar*>(result.c_str()),
        static_cast<jsize>(result.size()));
}