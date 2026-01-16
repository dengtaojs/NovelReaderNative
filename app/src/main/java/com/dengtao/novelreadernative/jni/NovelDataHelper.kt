package com.dengtao.novelreadernative.jni

import java.nio.ByteBuffer

object NovelDataHelper
{
    /**
     * 根据字节数组，创建一个新的对象。c++ 中始终只有一个 NovelData 对象。
     */
    external fun create(buffer: ByteBuffer) : Boolean

    /**
     * 删除 c++ 中的 NovelData 对象。
     */
    external fun delete()

    /**
     * 查找所有的标题位置。
     * @return 返回章的数量。
     */
    external fun findTitlePositions() : Int

    /**
     * 获取章的全部内容，包括标题。
     */
    external fun getChapterContent(index: Int) : String

}