package jni.http;


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
    public static native String httpFromJNITest();
    public static native String httpGET(String url,String params,String header);
    public static native JSONObject httpPOST(String url,JSONObject params,String header);

    public static native byte[] HmacSha256(byte[] data);
}
