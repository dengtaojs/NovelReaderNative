package com.dengtao.novelreadernative.jni

import java.nio.ByteBuffer

object NativeHelper
{
    external fun getStringFromByteBuffer(buffer: ByteBuffer) : String
}