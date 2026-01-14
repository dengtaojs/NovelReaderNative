//
// Created by Dengt on 1/13/2026.
//

#ifndef NOVELREADERNATIVE_U16DECODER_H
#define NOVELREADERNATIVE_U16DECODER_H
#include <string>
#include <unicode/ucnv.h>

namespace novel
{
    class U16Decoder
    {
    private:
        UConverter* m_converter {nullptr};

    public:
        U16Decoder() = default;
        ~U16Decoder();

        /**
         * 把输入的字节数组转换成 Unicode 16 字符串。 函数内部会解码确认字符集。
         * @param data 字节数组。
         * @param size 字节数组长度。
         * @return 返回字节数组对应的 UTF-16 字符串。如果失败，返回空白字符串。
         */
        std::u16string toUtf16(const char* data, size_t size);
    };
}




#endif //NOVELREADERNATIVE_U16DECODER_H
