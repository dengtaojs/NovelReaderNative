//
// Created by Dengt on 1/13/2026.
//

#ifndef NOVELREADERNATIVE_TEXTTOOLS_H
#define NOVELREADERNATIVE_TEXTTOOLS_H

#include <string>

namespace novel
{
    /**
     * 从字节数组中，获取对应的文本字符集名称。
     * @param data 数组对应的字节数组。
     * @param size 数据的字节数量。
     * @return 标准的字符集名称。如果失败，返回 “"。
     */
    std::string getCharset(const char* data, size_t size);

}

#endif //NOVELREADERNATIVE_TEXTTOOLS_H
