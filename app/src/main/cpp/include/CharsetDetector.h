//
// Created by DengTao on 1/15/2026.
//

#ifndef NOVELREADERNATIVE_CHARSETDETECTOR_H
#define NOVELREADERNATIVE_CHARSETDETECTOR_H
#include <string>

namespace novel
{
    class CharsetDetector
    {
    public:
        CharsetDetector();
        ~CharsetDetector();

        std::string getCharset(const std::string& text) const;
        std::string getCharset(const char* data, int32_t size) const;

    private:
        void* m_detector { nullptr };
    };
} // novel

#endif //NOVELREADERNATIVE_CHARSETDETECTOR_H
