//
// Created by DengTao on 1/16/2026.
//
#include <jni.h>
#include "NovelData.h"
#include "CharsetDetector.h"
#include "UnicodeConverter.h"

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_dengtao_novelreadernative_jni_NovelDataHelper_create(
        JNIEnv* env, jobject thiz, jobject buffer)
{
    // 1. 获取 buffer 的地址和长度
    const char* data = reinterpret_cast<char*>(env->GetDirectBufferAddress(buffer));
    auto srcSize = static_cast<int32_t>(env->GetDirectBufferCapacity(buffer));

    // 2. 获取编码名
    novel::CharsetDetector charsetDetector;
    std::string charset = charsetDetector.getCharset(data, srcSize);

    try {
        // 3. 获取 utf-16 字符串
        novel::UnicodeConverter unicodeConverter { charset };
        std::u16string result = unicodeConverter.toUtf16(data, srcSize);

        // 4. 创建 NovelData 对象
        novel::NovelData::current = std::make_shared<novel::NovelData>(result);
        return true;

    }
    catch (std::exception const&) {
        return false;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_dengtao_novelreadernative_jni_NovelDataHelper_delete(
        JNIEnv* env, jobject thiz)
{
    novel::NovelData::current.reset();
}


extern "C"
JNIEXPORT jint JNICALL
Java_com_dengtao_novelreadernative_jni_NovelDataHelper_findTitlePositions(JNIEnv* env, jobject thiz)
{
    if (novel::NovelData::current != nullptr) {
        novel::NovelData::current->splitNovel();
        return novel::NovelData::current->size();
    }
    else {
        return 0;
    }
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_dengtao_novelreadernative_jni_NovelDataHelper_getChapterContent(
        JNIEnv* env, jobject thiz, jint index)
{
    if (novel::NovelData::current != nullptr) {
        std::u16string text { novel::NovelData::current->getChapterContent(index) };
        return env->NewString(
                reinterpret_cast<const jchar*>(text.c_str()),static_cast<jsize>(text.size()));
    }
    else {
        return env->NewStringUTF("");
    }
}