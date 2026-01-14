package com.dengtao.novelreadernative

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.Scaffold
import androidx.compose.ui.Modifier
import com.dengtao.novelreadernative.ui.theme.NovelReaderNativeTheme
import com.dengtao.novelreadernative.view.MainPage

class MainActivity : ComponentActivity()
{
    companion object{
        init {
            System.loadLibrary("novelreadernative")
        }
    }

    override fun onCreate(savedInstanceState: Bundle?)
    {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            NovelReaderNativeTheme {
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    MainPage(innerPadding)
                }
            }
        }
    }
}