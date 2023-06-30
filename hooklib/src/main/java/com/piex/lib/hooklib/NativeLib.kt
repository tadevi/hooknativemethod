package com.piex.lib.hooklib

object NativeLib {
    fun init() {
        System.loadLibrary("hooklib")
    }
}