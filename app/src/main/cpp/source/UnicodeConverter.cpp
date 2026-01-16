//
// Created by DengTao on 1/15/2026.
//

#include "UnicodeConverter.h"
#include <unicode/ucnv.h>
#include <unicode/ustring.h>

namespace novel
{
    UnicodeConverter::UnicodeConverter(const std::string& srcCharset)
    {
        UErrorCode errorCode = UErrorCode::U_ZERO_ERROR;
        m_converter = ucnv_open(srcCharset.c_str(), &errorCode);

        if (U_FAILURE(errorCode)) {
            throw std::runtime_error("错误：不支持的字符集名称" + srcCharset);
        }
    }

    UnicodeConverter::~UnicodeConverter()
    {
        if (m_converter) {
            auto converter = static_cast<UConverter*>(m_converter);
            ucnv_close(converter);
        }
    }

    std::u16string UnicodeConverter::toUtf16(const char* data, int32_t srcSize) const
    {
        UErrorCode errorCode = UErrorCode::U_ZERO_ERROR;
        auto converter = static_cast<UConverter*>(m_converter);

        int32_t sizeNeeded = ucnv_toUChars(converter, nullptr, 0, data, srcSize, &errorCode);
        if (errorCode != UErrorCode::U_BUFFER_OVERFLOW_ERROR) {
            return std::u16string { };
        }

        errorCode = UErrorCode::U_ZERO_ERROR;
        ++sizeNeeded;
        std::u16string result(sizeNeeded, u'\0');
        ucnv_toUChars(converter, result.data(), sizeNeeded, data, srcSize, &errorCode);

        if (U_SUCCESS(errorCode)) {
            return result;
        }
        return std::u16string { };
    }

    std::u16string UnicodeConverter::toUtf16(const std::string& text) const
    {
        return this->toUtf16(text.c_str(), static_cast<int32_t>(text.size()));
    }
} // novel