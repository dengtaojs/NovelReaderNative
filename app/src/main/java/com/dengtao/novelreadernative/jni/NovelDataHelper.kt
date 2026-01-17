package com.dengtao.novelreadernative.jni

import java.nio.ByteBuffer

object NovelDataHelper
{
    /**
     * 根据字节数组，创建一个新的对象。c++ 中始终只有一个 NovelData 对象。
     */
    external fun create(buffer: ByteBuffer) : Int

    /**
     * 删除 c++ 中的 NovelData 对象。
     */
    external fun delete()

    /**
     * 获取章的全部内容，不包括标题。
     */
    external fun getText(index: Int) : String

    /**
     * 获取章的标题。
     */
    external fun getTitle(index: Int) : String

    external fun getContent(index: Int) : String

}