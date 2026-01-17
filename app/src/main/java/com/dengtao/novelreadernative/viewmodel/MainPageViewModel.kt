package com.dengtao.novelreadernative.viewmodel

import android.app.Application
import android.content.Context
import android.net.Uri
import androidx.lifecycle.AndroidViewModel
import com.dengtao.novelreadernative.jni.NovelDataHelper
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.withContext
import java.io.FileInputStream
import java.nio.ByteBuffer

class MainPageViewModel(application: Application)
    : AndroidViewModel(application)
{
    val chapterTitle = MutableStateFlow("章标题")
    val chapterText = MutableStateFlow("章内容")
    val executeTime = MutableStateFlow("执行时间")
    var totalChapters = 0
    var chaptersCount = 0
    var index = 0;

    suspend fun openFileAsync(context: Context, uri: Uri)
    {
        withContext(Dispatchers.IO) {
            context.contentResolver.openFileDescriptor(uri, "r")?.use { parcelFileDescriptor ->
                val t0 = System.currentTimeMillis()
                val fileInputStream = FileInputStream(parcelFileDescriptor.fileDescriptor)
                val channel = fileInputStream.channel

                val buffer = ByteBuffer.allocateDirect(channel.size().toInt())
                channel.read(buffer)
                buffer.flip()
                val t1 = System.currentTimeMillis()
                totalChapters = NovelDataHelper.create(buffer);
                buffer.clear();

                if (totalChapters > 0) {
                    val t2 = System.currentTimeMillis()
                    updateTitleAndText(0)
                    executeTime.value = "Kotlin 中用时：${t1 - t0} ms， C++ 中用时: ${t2 - t1} ms"
                }
            }
        }
    }

    fun updateTitleAndText(index: Int)
    {
        val fullContent = NovelDataHelper.getContent(index)
        if (fullContent.isEmpty()) {
            chapterText.value = ""
            chapterTitle.value = ""
        } else {
            val lineBreakPos = fullContent.indexOfFirst { c-> c == '\n' || c == '\r' }
            chapterTitle.value = fullContent.substring(0..< lineBreakPos).trimEnd()
            chapterText.value = fullContent.substring(lineBreakPos + 1).trimStart()
        }
    }

    fun readPrevious()
    {
        if (index == 0) return
        --index
        chapterTitle.value = NovelDataHelper.getTitle(index);
        chapterText.value = NovelDataHelper.getText(index)
    }

    fun readNext()
    {
        if (index == chaptersCount - 1) return
        ++index
        chapterText.value = NovelDataHelper.getText(index)
        chapterTitle.value = NovelDataHelper.getTitle(index);
    }

    fun delete()
    {
        NovelDataHelper.delete()
    }
}