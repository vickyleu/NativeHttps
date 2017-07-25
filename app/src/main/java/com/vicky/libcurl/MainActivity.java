package com.vicky.libcurl;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Base64;
import android.util.Log;
import android.widget.TextView;

import jni.http.CppProxy;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = MainActivity.class.getSimpleName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        // Example of a call to a native method
        final TextView tv = (TextView) findViewById(R.id.sample_text);

//        byte[] result = CppProxy.HmacSha256("你们好啊".getBytes());
        String result2 = CppProxy.AesEncrypt("超级工厂");
        Log.e("AesEncrypt",result2);
        String result3 = CppProxy.AesDecrypt(result2);
        Log.e("AesDecrypt",result3);




//        final String b64 = Base64.encodeToString(result, Base64.DEFAULT);
//        Log.e(TAG, "HmacSha256>>>>>>>>>>>>>" + b64);
//        tv.setText(result3);


 /*
//         * 此处使用AES-128-ECB加密模式，key需要为16位。
//         */
//        String cKey = "12347895a2d5q6c5";
//        // 需要加密的字串
//        String cSrc = "超级工厂";
//        try {
//            // 加密
//            String enString = AesUtils.Encrypt(cSrc, cKey);
//            Log.e("加密:",enString+"");
//            // 解密
//            String DeString = AesUtils.Decrypt(enString, cKey);
//            Log.e("解密:",DeString+"");
//        }catch (Exception e){
//            e.printStackTrace();
//        }



//        for (int i = 0; i < 1; i++) {
//            new Thread(new Runnable() {
//                @Override
//                public void run() {
//                    runOnUiThread(new Runnable() {
//                        @Override
//                        public void run() {
//
//                        }
//                    });
//                    try {
//                        Thread.sleep(200);
//                    } catch (InterruptedException e) {
//                        e.printStackTrace();
//                    }
//                }
//            }).start();
//        }





//        new Thread(new Runnable() {
//            @Override
//            public void run() {
////                final String s = CppProxy.httpFromJNITest();
//                Log.e(TAG, "httpFromJNI>>>>>>>>>>>>>" /*+ s*/);
//                runOnUiThread(new Runnable() {
//                    @Override
//                    public void run() {
//                        tv.setText(b64 + "\n\n" /*+ s*/);
//                    }
//                });
//            }
//        }).start();
//
//        new Thread(new Runnable() {
//            @Override
//            public void run() {
////                Object ss = CppProxy.httpGET("https://saas.51cjgc.com/api/statistics/loadData", null,
//                Object ss = CppProxy.httpGET("http://120.25.195.170:8880/api/statistics/loadData", null,
//                        "token :58a1ab3c0b001d40b1e247b3c9ed794");
//                Log.e(TAG, "onCreate: " + ss.toString());
//            }
//        }).start();
//
//        ImageScanner mScanner = new ImageScanner();
//        mScanner.setConfig(0, Config.X_DENSITY, 3);
//        mScanner.setConfig(0, Config.Y_DENSITY, 3);


    }

}
