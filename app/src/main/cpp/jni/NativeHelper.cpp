#include <jni.h>
#include "CharsetDetector.h"
#include "UnicodeConverter.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_dengtao_novelreadernative_jni_NativeHelper_getStringFromByteBuffer(
    JNIEnv *env,
    jobject thiz,
    jobject buffer)
{
    // 1. 获取 buffer 的地址和长度
    const char* data = reinterpret_cast<char*>(env->GetDirectBufferAddress(buffer));
    auto size = static_cast<size_t>(env->GetDirectBufferCapacity(buffer));

    // 2. 获取编码名
    std::string charset = novel::detectEncoding(data, size);

    try{
        // 3. 获取 utf-16 字符串
        novel::UnicodeConverter unicodeConverter { charset };
        std::u16string result = unicodeConverter.toUtf16(data, size);
        return env->NewString(
            reinterpret_cast<const jchar*>(result.c_str()), static_cast<jsize>(result.size())
        );
    }
    catch (std::exception const& exception) {
        std::string errorMessage {exception.what()};
        return env->NewStringUTF(errorMessage.c_str());
    }
}