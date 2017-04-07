package com.example.yao.jnimd5;

/**
 * Created by yao on 2017/3/28.
 */

public class Md5Utils {
    static {
        System.loadLibrary("jniMd5"); //defaultConfig.ndk.moduleName
    }

    public static native String getRandomNum(String timestamp, boolean uppercase);
}
