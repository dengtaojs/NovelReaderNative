//
// Created by DengTao on 1/17/2026.
//

#include "XwTools.h"
#include <uchardet/uchardet.h>
#include <unicode/ucnv.h>

std::string xw::detectCharset(const char* data, size_t len)
{
    uchardet_t detector = uchardet_new();

    size_t dataLength = minOf(len, 8192ul);
    uchardet_handle_data(detector, data, dataLength);
    uchardet_data_end(detector);

    std::string charsetName { uchardet_get_charset(detector) };
    uchardet_delete(detector);
    return charsetName;
}

std::u16string xw::toUtf16(const char* data, size_t len, const std::string& charset)
{
    int32_t dataLength = static_cast<int32_t>(len);
    int32_t sizeNeeded {};
    std::u16string result;

    UErrorCode errorCode = UErrorCode::U_ZERO_ERROR;
    UConverter* converter = ucnv_open(charset.c_str(), &errorCode);
    if (U_FAILURE(errorCode)) {
        goto END;
    }

    // 计算需要的长度
    sizeNeeded = ucnv_toUChars(converter, nullptr, 0, data, dataLength, &errorCode);
    if (errorCode != UErrorCode::U_BUFFER_OVERFLOW_ERROR){
        goto END;
    }

    // 执行转换
    sizeNeeded++;
    errorCode = UErrorCode::U_ZERO_ERROR;
    result.resize(sizeNeeded, u'\0');
    ucnv_toUChars(converter, result.data(), sizeNeeded, data, dataLength, &errorCode);
    if (U_FAILURE(errorCode)) {
        result.clear();
    }

END:
    ucnv_close(converter);
    return result;
}