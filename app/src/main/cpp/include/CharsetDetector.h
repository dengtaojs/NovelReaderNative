//
// Created by DengTao on 1/15/2026.
//

#ifndef NOVELREADERNATIVE_CHARSETDETECTOR_H
#define NOVELREADERNATIVE_CHARSETDETECTOR_H
#include <string>

namespace novel
{
    std::string detectEncoding(const char* data, int len);
} // novel

#endif //NOVELREADERNATIVE_CHARSETDETECTOR_H
