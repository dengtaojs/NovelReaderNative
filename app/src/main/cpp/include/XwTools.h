//
// Created by DengTao on 1/17/2026.
//

#ifndef NOVELREADERNATIVE_XWTOOLS_H
#define NOVELREADERNATIVE_XWTOOLS_H

#include <string>

namespace xw
{
    /**
     * 返回两个可比较值的最小值。
     * @tparam T
     * @param t1
     * @param t2
     * @return
     */
    template<typename T>
    T minOf(const T& t1, const T& t2)
    {
        return (t1 <= t2) ? t1 : t2;
    }

    /**
     * 返回两个可比较值的最大值。
     * @tparam T
     * @param t1
     * @param t2
     * @return
     */
    template<typename T>
    T maxOf(const T& t1, const T& t2)
    {
        return (t1 >= t2) ? t1 : t2;
    }

    /**
     * 检测字节数组的编码。
     * @param data
     * @param len
     * @return 返回标准的字符编码名称。如果失败，返回空字符串。
     */
    std::string detectCharset(const char* data, size_t len);

    /**
     * 根据给定的字符集名称，字节数组转换成 UTF16 字符串。
     * @param data 原始字节数组。
     * @param len 原始字节数组长度。
     * @param charset 原始字节编码名称。
     * @return UTF16字符串。如果失败返回空字符串。
     */
    std::u16string toUtf16(const char* data, size_t len, std::string const& charset);
}


#endif //NOVELREADERNATIVE_XWTOOLS_H
