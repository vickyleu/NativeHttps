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
//        if (Build.VERSION.SDK_INT==Build.VERSION_CODES.JELLY_BEAN_MR1) {
//            System.loadLibrary("opencv_java");
//        }
//        System.loadLibrary("stlport_shared");
//        System.loadLibrary("gnustl_shared");
        System.loadLibrary("c++_shared");
        System.loadLibrary("curl");
        System.loadLibrary("Zbar");
        System.loadLibrary("jsonlib");
        System.loadLibrary("native");

    }


    public static void init() {
//        loadLibs();
    }

    //    public static native void loadLibs();
    @WorkerThread
    public static native String httpFromJNITest();

    @WorkerThread
    public static native String httpGET(String url, String params, String header);

    @WorkerThread
    public static native String httpPOST(String url, JSONObject params, String header);

    public static native byte[] HmacSha256(byte[] data);

    public static native String AesEncrypt(String plainText);

    public static native String AesDecrypt(String cipherText);

}
