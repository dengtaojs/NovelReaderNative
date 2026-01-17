//
// Created by DengTao on 1/16/2026.
//

#ifndef NOVELREADERNATIVE_NOVELDATA_H
#define NOVELREADERNATIVE_NOVELDATA_H

#include <string>
#include <vector>
#include <memory>

namespace novel
{
    class NovelData
    {
    public:
        static std::shared_ptr<NovelData> current;
        static void* titleRegexPattern;

        explicit NovelData(std::u16string const&  fileContent);

        /**
         * 根据章的索引，获取章的内容。
         * @param index
         * @return 如果失败，返回空字符串。
         */
        std::u16string getText(size_t index) const;

        /**
         * 根据章的索引，获取标题字符串。
         * @param index
         * @return 如果失败，返回空字符串。
         */
        std::u16string getTitle(size_t index) const;

        /**
         * 获取章的所有内容。
         * @param index
         * @return 如果失败返回空字符串。
         */
        std::u16string getContent(size_t index) const;


        /**
         * 获取章的总数。
         * @return 章的总数。如果分章失败，返回 0.
         */
        int32_t totalChapters() const { return static_cast<int32_t>(m_titlePositions.size()); }

        /**
         * 查找所有标题的位置，结果保存在 m_titlePositions 中。
         */
        void splitNovel();


    private:
        std::vector<size_t> splitBlock(size_t startPos, size_t len);

        std::u16string m_fileContent;
        std::vector<size_t> m_titlePositions;
    };
}


#endif //NOVELREADERNATIVE_NOVELDATA_H
