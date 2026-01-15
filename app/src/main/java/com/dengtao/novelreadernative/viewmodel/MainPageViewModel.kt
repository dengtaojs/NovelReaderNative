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
    val fileContent = MutableStateFlow("文件内容")
    val executeTime = MutableStateFlow("运行时间")


    suspend fun openFileAsync(context: Context, uri: Uri)
    {
        withContext(Dispatchers.IO) {
            context.contentResolver.openFileDescriptor(uri, "r")?.use { parcelFileDescriptor ->
                val fileInputStream = FileInputStream(parcelFileDescriptor.fileDescriptor)
                val channel = fileInputStream.channel

                val buffer = ByteBuffer.allocateDirect(channel.size().toInt())
                channel.read(buffer)
                buffer.flip()
                val content = NativeHelper.getStringFromByteBuffer(buffer)
                buffer.clear();
                fileContent.value = content.take(5000)
            }
        }

    }
}