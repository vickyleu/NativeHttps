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
        byte[] result = CppProxy.HmacSha256("你们好啊".getBytes());
        final String b64 = Base64.encodeToString(result, Base64.DEFAULT);
        Log.e(TAG, "HmacSha256>>>>>>>>>>>>>" + b64);

        new Thread(new Runnable() {
            @Override
            public void run() {
//                final String s = CppProxy.httpFromJNITest();
                Log.e(TAG, "httpFromJNI>>>>>>>>>>>>>" /*+ s*/);
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        tv.setText(b64 + "\n\n" /*+ s*/);
                    }
                });
            }
        }).start();

        new Thread(new Runnable() {
            @Override
            public void run() {
//                Object ss = CppProxy.httpGET("https://saas.51cjgc.com/api/statistics/loadData", null,
                Object ss = CppProxy.httpGET("https://120.25.195.170:8880/api/statistics/loadData", null,
                        "token :58a1ab3c0b001d40b1e247b3c9ed794");
                Log.e(TAG, "onCreate: " + ss.toString());
            }
        }).start();


    }

}
