package com.vicky.libcurl;

import android.app.Application;

import jni.http.JniApp;

/**
 * Created by VickyLeu on 2017/5/9.
 *
 * @Author VickyLeu
 * @Date 2017年05月09日 17点25分
 * @ClassName 此处填写类名
 */

public class App extends Application {
    @Override
    public void onCreate() {
        super.onCreate();
        JniApp.install(this);
    }
}
