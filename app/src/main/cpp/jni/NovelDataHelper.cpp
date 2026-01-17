//
// Created by DengTao on 1/16/2026.
//
#include <jni.h>
#include "NovelData.h"
#include "XwTools.h"

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_dengtao_novelreadernative_jni_NovelDataHelper_create(
        JNIEnv* env, jobject thiz, jobject buffer)
{
    bool result {false};
    std::u16string fileContent;

    // 1. 获取 buffer 的地址和长度
    const char* data = reinterpret_cast<char*>(env->GetDirectBufferAddress(buffer));
    auto dataLength = static_cast<int32_t>(env->GetDirectBufferCapacity(buffer));

    // 2. 获取编码名
    std::string charset = xw::detectCharset(data, dataLength);
    if (charset.empty()) {
        goto END;
    }

    // 3. 执行转换
    fileContent = xw::toUtf16(data, dataLength, charset);
    if (charset.empty()) {
        goto END;
    }

    // 4. 创建 ChapterData 对象
    novel::NovelData::current = std::make_shared<novel::NovelData>(fileContent);
    result = true;

END:
    return result;
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
    return 0;
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_dengtao_novelreadernative_jni_NovelDataHelper_getChapterContent(
        JNIEnv* env, jobject thiz, jint index)
{
    if (novel::NovelData::current != nullptr) {
        std::u16string text { novel::NovelData::current->getChapterContent(index) };
        return env->NewString(
                reinterpret_cast<const jchar*>(text.c_str()),
                static_cast<jsize>(text.size())
        );
    }
    return env->NewStringUTF("");
}