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
        explicit NovelData(std::u16string const&  fileContent);
        std::u16string getChapterContent(size_t index) const;
        std::u16string getTitle(size_t index) const;

        int32_t size() const;
        void splitNovel();

    public:
        static std::shared_ptr<NovelData> current;

    private:
        static void* titileRegex;

        std::u16string m_fileContent;
        std::vector<size_t> m_titlePositions;
    };
}


#endif //NOVELREADERNATIVE_NOVELDATA_H
