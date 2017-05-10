package jni.http;

import android.app.Application;
import android.content.Context;
import android.util.Log;

import jni.http.Exception.NativeCrashHandler;

/**
 * Created by VickyLeu on 2017/5/9.
 *
 * @Author VickyLeu
 * @Date 2017年05月09日 17点15分
 * @ClassName 此处填写类名
 */

public class JniApp {
    public static void install(Context app) {
        try {
            if (app == null) {
                error();
                return;
            } else if (!(app instanceof Application)) {
                Context ctx = app.getApplicationContext();
                install(ctx);
                return;
            }
            NativeCrashHandler.getHandler().registerForNativeCrash(app);
        } catch (Exception ignored) {
        }
    }

    private static void error() {
        Log.w("JniApp", "Failure to install native vicky-http library");
    }
}
