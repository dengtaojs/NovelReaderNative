//
// Created by DengTao on 1/15/2026.
//

#ifndef NOVELREADERNATIVE_UNICODECONVERTER_H
#define NOVELREADERNATIVE_UNICODECONVERTER_H

#include <string>

namespace novel
{

    class UnicodeConverter
    {
    public:
        explicit UnicodeConverter(std::string const& srcCharset);
        ~UnicodeConverter();

        std::u16string toUtf16(const char* data, int32_t srcSize) const;
        std::u16string toUtf16(const std::string& text) const;

    private:
        void* m_converter {nullptr};
    };

} // novel

#endif //NOVELREADERNATIVE_UNICODECONVERTER_H
