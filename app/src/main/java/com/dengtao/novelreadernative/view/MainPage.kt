package com.dengtao.novelreadernative.view

import androidx.activity.compose.rememberLauncherForActivityResult
import androidx.activity.result.contract.ActivityResultContracts
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.verticalScroll
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.FileOpen
import androidx.compose.material3.Button
import androidx.compose.material3.Card
import androidx.compose.material3.Icon
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.rememberCoroutineScope
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.unit.dp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.lifecycle.viewmodel.compose.viewModel
import com.dengtao.novelreadernative.viewmodel.MainPageViewModel
import kotlinx.coroutines.launch

@Composable
fun MainPage(innerPadding: PaddingValues)
{
    val vm: MainPageViewModel = viewModel()
    val fileContent by vm.fileContent.collectAsStateWithLifecycle()
    val executeTime by vm.executeTime.collectAsStateWithLifecycle()

    val context = LocalContext.current

    val scope = rememberCoroutineScope()
    val filePicker = rememberLauncherForActivityResult(ActivityResultContracts.OpenDocument()) { uri ->
        uri?.let { scope.launch { vm.openFileAsync(context, it) } }
    }

    Column(
        modifier = Modifier.fillMaxSize().padding(innerPadding).padding(horizontal = 10.dp, vertical = 5.dp),
        verticalArrangement = Arrangement.spacedBy(5.dp)
    ) {
        Button({ filePicker.launch(arrayOf("text/plain")) }) {
            Row(horizontalArrangement = Arrangement.spacedBy(5.dp)) {
                Icon(Icons.Default.FileOpen, null)
                Text("打开文件")
            }
        }

        Card(Modifier.fillMaxSize().weight(0.2f)) {
            Text(
                text = executeTime,
                style = MaterialTheme.typography.bodySmall
            )
        }

        Box(Modifier.fillMaxSize().weight(1f).verticalScroll(rememberScrollState())) {
            Text(
                text = fileContent,
                style = MaterialTheme.typography.bodyMedium
            )
        }
    }
}