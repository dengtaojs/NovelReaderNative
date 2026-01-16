//
// Created by DengTao on 1/15/2026.
//

#include "CharsetDetector.h"
#include <uchardet/uchardet.h>

namespace novel
{
    CharsetDetector::CharsetDetector()
    {
        m_detector = uchardet_new();
    }

    CharsetDetector::~CharsetDetector()
    {
        if (m_detector) {
            uchardet_delete(static_cast<uchardet_t>(m_detector));
        }
    }

    std::string CharsetDetector::getCharset(const char* data, int32_t size) const
    {
        auto detector = static_cast<uchardet_t>(m_detector);

        uchardet_reset(detector);
        uchardet_handle_data(detector, data, size);
        uchardet_data_end(detector);

        std::string charset { uchardet_get_charset(detector) };
        return charset;
    }

    std::string CharsetDetector::getCharset(const std::string& text) const
    {
        return this->getCharset(text.c_str(), static_cast<int32_t>(text.size()));
    }
} // novel