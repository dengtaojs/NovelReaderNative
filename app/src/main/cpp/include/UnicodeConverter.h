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

        std::u16string toUtf16(const char* data, size_t size);
        std::u16string toUtf16(const std::string& text);

    private:
        void* m_converter {nullptr};
    };

} // novel

#endif //NOVELREADERNATIVE_UNICODECONVERTER_H
