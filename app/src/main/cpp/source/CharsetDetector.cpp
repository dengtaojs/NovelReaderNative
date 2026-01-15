//
// Created by DengTao on 1/15/2026.
//

#include "CharsetDetector.h"
#include <compact_enc_det/compact_enc_det.h>

namespace novel
{
    // TODO 需要调试
    // 编译失败
    std::string detectEncoding(const char *data, int len)
    {
        bool isReliable { false };
        int bytesConsumed { 0 };

        Encoding encoding = CompactEncDet::DetectEncoding(
                data, len, nullptr, nullptr, nullptr, Encoding::CHINESE_GB, Language::CHINESE,
                CompactEncDet::WEB_CORPUS, false, &bytesConsumed, &isReliable);

        auto name = EncodingName(encoding);
        return std::string {name};
    }
} // novel