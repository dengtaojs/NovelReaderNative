package com.dengtao.novelreadernative.viewmodel

import android.app.Application
import android.content.Context
import android.net.Uri
import androidx.lifecycle.AndroidViewModel
import com.dengtao.novelreadernative.jni.NativeHelper
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.withContext
import java.io.FileInputStream
import java.nio.ByteBuffer

class MainPageViewModel(application: Application)
    : AndroidViewModel(application)
{
    val executeTime = MutableStateFlow("")
    val fileContent = MutableStateFlow("文件内容")

    suspend fun openFileAsync(context: Context, uri: Uri)
    {
        withContext(Dispatchers.IO) {
            context.contentResolver.openFileDescriptor(uri, "r")?.use { parcelFileDescriptor ->
                val start = System.currentTimeMillis()
                val fileInputStream = FileInputStream(parcelFileDescriptor.fileDescriptor)
                val channel = fileInputStream.channel

                val buffer = ByteBuffer.allocateDirect(channel.size().toInt())
                channel.read(buffer)
                buffer.flip()
                val t1 = System.currentTimeMillis()
                val content = NativeHelper.getStringFromByteBuffer(buffer)
                val t2 = System.currentTimeMillis()

                fileContent.value = content.take(2000)
                executeTime.value = "分配空间用时 ${t1 - start} ms， 调用 c++ 函数用时 ${t2 - t1} ms"
            }
        }
    }
}