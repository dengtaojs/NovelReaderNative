//
// Created by DengTao on 1/16/2026.
//

#include "NovelData.h"
#include <unicode/regex.h>
#include <unicode/unistr.h>

void* novel::NovelData::titileRegex { nullptr };
std::shared_ptr<novel::NovelData> novel::NovelData::current { nullptr };

template<typename T>
T MY_MAX(T v1, T v2)
{
    return (v1 >= v2) ? v1 : v2;
}

template<typename T>
T MY_MIN(T v1, T v2)
{
    return (v1 <= v2) ? v1 : v2;
}

namespace novel
{
    NovelData::NovelData(const std::u16string& fileContent)
            : m_fileContent{ std::move(fileContent) }
    {
        icu::UnicodeString s1 { u"hekko"};
        icu::UnicodeString s2 { std::move(s1) };

    }

    void NovelData::splitNovel()
    {
        UErrorCode errorCode = UErrorCode::U_ZERO_ERROR;

        if (titileRegex == nullptr) {
            UParseError parseError;
            titileRegex = icu::RegexPattern::compile(
                    uR"(第\s?[\d一二三四五六七八九十零百千万]+\s?章)", parseError, errorCode);
        }

        auto titlePattern = static_cast<icu::RegexPattern*>(titileRegex);

        size_t startPos = 0;
        size_t remainSize = m_fileContent.size();

        m_titlePositions.push_back(0);
        constexpr size_t BLOCK_SIZE {512 * 1024};

        while (remainSize > 0) {
            size_t subStrSize = MY_MIN (BLOCK_SIZE, remainSize);
            remainSize -= subStrSize;

            std::u16string subStr = m_fileContent.substr(startPos, subStrSize);

            errorCode = UErrorCode::U_ZERO_ERROR;
            icu::RegexMatcher* matcher = titlePattern->matcher(subStr, errorCode);
            if (U_FAILURE(errorCode)) {
                break;
            }

            while (matcher->find() && U_SUCCESS(errorCode)) {
                size_t start = matcher->start(errorCode) + startPos;
                if (start != 0) {
                    m_titlePositions.push_back(start);
                }
            }

            startPos += subStrSize;
        }
    }

    std::u16string NovelData::getChapterContent(size_t index) const
    {
        if (index >= m_titlePositions.size()) {
            return {};
        }

        size_t startPos = m_titlePositions[index];

        if (index + 1 == m_titlePositions.size()) {
            return m_fileContent.substr(startPos);
        }
        else {
            size_t endPos = m_titlePositions[index + 1];
            return m_fileContent.substr(startPos, endPos - startPos);
        }
    }

    int32_t NovelData::size() const
    {
        return static_cast<int32_t>(m_titlePositions.size());
    }

    std::u16string NovelData::getTitle(size_t index) const
    {
        if (index >= m_titlePositions.size()) {
            return {};
        }

        size_t startPos = m_titlePositions[index];
        size_t endPos = startPos + 1;

        while (endPos < m_fileContent.size()) {
            char16_t c = m_fileContent[endPos];
            if (c == u'\r' || c == u'\n') {
                break;
            }
            ++endPos;
        }

        return m_fileContent.substr(startPos, endPos - startPos);
    }
}
