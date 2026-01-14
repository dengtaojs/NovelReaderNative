//
// Created by Dengt on 1/13/2026.
//

#include "U16Decoder.h"
#include "TextTools.h"

constexpr std::u16string EMPTY_U16_STR {};


novel::U16Decoder::~U16Decoder()
{
    if (m_converter != nullptr) {
        ucnv_close(m_converter);
    }
}

std::u16string novel::U16Decoder::toUtf16(const char *data, size_t size)
{
    // 1. 确认字符集
    std::string charset = novel::getCharset(data, size);
    if (charset.empty()) {
        return EMPTY_U16_STR;
    }

    UErrorCode status = U_ZERO_ERROR;
    if (m_converter) ucnv_close(m_converter);

    // 2. 创建转换器
    m_converter = ucnv_open(charset.c_str(), &status);
    if (U_FAILURE(status)) {
        return EMPTY_U16_STR;
    }

    // 3. 确认需要的 UTF-16 字符数量。
    int32_t sizeInput = static_cast<int32_t>(size);
    int32_t sizeNeed = ucnv_toUChars_78(m_converter, nullptr, 0, data, sizeInput, &status);

    // 4. 开始转换
    sizeNeed += 1;
    status = U_ZERO_ERROR;
    std::u16string result(sizeNeed, u'\0');
    ucnv_toUChars(m_converter, result.data(), sizeNeed, data, sizeInput, &status);

    return U_SUCCESS(status) ? result : EMPTY_U16_STR;
}
