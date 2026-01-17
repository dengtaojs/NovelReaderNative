//
// Created by DengTao on 1/16/2026.
//

#include "NovelData.h"
#include "XwTools.h"
#include <future>
#include <unicode/regex.h>
#include <unicode/unistr.h>

std::shared_ptr<novel::NovelData> novel::NovelData::current { nullptr };
void* novel::NovelData::titleRegexPattern { nullptr };

namespace novel
{
    NovelData::NovelData(const std::u16string& fileContent)
            : m_fileContent{ std::move(fileContent) }
    {
        if (titleRegexPattern == nullptr) {
            UParseError parseError;
            UErrorCode errorCode = UErrorCode::U_ZERO_ERROR;
            icu::UnicodeString titleRegex {uR"(第[\s\d一二三四五六七八九十零百千万]+章)"};
            titleRegexPattern = icu::RegexPattern::compile(titleRegex, parseError, errorCode);
        }
    }

    void NovelData::splitNovel()
    {
        using task_type = std::future<std::vector<size_t>>;
        std::vector<task_type> tasks;

        constexpr size_t BLOCK_SIZE { 512 * 1024 };
        size_t remainSize = m_fileContent.size();
        size_t startPos = 0;

        while(remainSize > 0) {
            size_t actualSize = xw::minOf(BLOCK_SIZE, remainSize);
            remainSize -= actualSize;

            tasks.push_back(std::async(std::launch::async, &NovelData::splitBlock, this, startPos, actualSize));
            startPos = actualSize;
        }

        m_titlePositions.push_back(0);
        for(task_type& task : tasks) {
            auto result = task.get();
            for(size_t pos : result) {
                m_titlePositions.push_back(pos);
            }
        }
        std::sort(m_titlePositions.begin(), m_titlePositions.end());
    }

    std::u16string NovelData::getText(size_t index) const
    {
        if (index >= m_titlePositions.size()) {
            return {};
        }

        size_t startPos = m_titlePositions[index];
        size_t endPos = (index + 1 >= m_titlePositions.size()) ? m_fileContent.size() : m_titlePositions[index + 1];
        size_t textStartPos = m_fileContent.find_first_of(u"\r\n", startPos) + 2;
        std::u16string text = m_fileContent.substr(textStartPos, endPos - textStartPos);
        return text;
    }


    std::u16string NovelData::getTitle(size_t index) const
    {
        if (index >= m_titlePositions.size()) {
            return {};
        }

        size_t startPos = m_titlePositions[index];
        size_t titleEndPos = m_fileContent.find_first_of(u"\r\n", startPos);
        std::u16string title = m_fileContent.substr(startPos, titleEndPos - startPos);
        return title;
    }

    std::vector<size_t> NovelData::splitBlock(size_t startPos, size_t len)
    {
        std::vector<size_t> result;
        UErrorCode errorCode = UErrorCode::U_ZERO_ERROR;

        auto pattern = (icu::RegexPattern*)titleRegexPattern;
        icu::UnicodeString input { m_fileContent.substr(startPos, len) };
        auto matcher = pattern->matcher(input, errorCode);

        while (matcher->find() && U_SUCCESS(errorCode)) {
            result.push_back(startPos + matcher->start(errorCode));
        }

        delete matcher;
        return result;
    }

    std::u16string NovelData::getContent(size_t index) const {
        if (index >= m_titlePositions.size()) {
            return {};
        }

        size_t startPos = m_titlePositions[index];
        size_t endPos = (index + 1 >= m_titlePositions.size()) ? m_fileContent.size() : m_titlePositions[index + 1];
        std::u16string chapterFullText = m_fileContent.substr(startPos, endPos);

        return chapterFullText;
    }
}
