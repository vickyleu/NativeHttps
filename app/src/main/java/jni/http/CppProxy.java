package jni.http;


import android.support.annotation.WorkerThread;

import com.vicky.libcurl.BuildConfig;

import org.json.JSONObject;

/**
 * Created by Administrator on 2016/12/15.
 */

public class CppProxy {
    public static final boolean isDebug = BuildConfig.DEBUG;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
        System.loadLibrary("jsonlib");
    }


    public static void init() {
    }
    @WorkerThread
    public static native String httpFromJNITest();
    @WorkerThread
    public static native String httpGET(String url,String params,String header);
    @WorkerThread
    public static native String httpPOST(String url,JSONObject params,String header);

    public static native byte[] HmacSha256(byte[] data);
}
