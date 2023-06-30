package com.piex.app.hooknativemethod

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import com.piex.lib.hooklib.NativeLib
import java.io.File
import kotlin.concurrent.thread
import kotlin.system.measureTimeMillis

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        NativeLib.init()
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        thread {
            File(cacheDir, "foo.txt").outputStream().use {
                it.write(ByteArray(100))
                measureTimeMillis {
                    Log.e("###", "start fsync")
                    it.fd.sync()
                    Log.e("###", "done fsync")
                }.also {
                    Log.e("###", "fsync=$it")
                }
            }
        }
    }
}