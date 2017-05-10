package com.vicky.libcurl;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Base64;
import android.util.Log;
import android.widget.TextView;

import org.json.JSONArray;
import org.json.JSONObject;
import org.json.JSONTokener;

import jni.http.CppProxy;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = MainActivity.class.getSimpleName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Class c;
        c.newInstance()
        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        byte[] result = CppProxy.HmacSha256("你们好啊".getBytes());
        String b64 = Base64.encodeToString(result, Base64.DEFAULT);
        Log.e(TAG, "HmacSha256>>>>>>>>>>>>>" + b64);
        String s = CppProxy.httpFromJNITest();
        String ss = CppProxy.httpGET("http://120.25.195.170:8880/api/statistics/loadData", null, "token :58a1ab3c0b001d40b1e247b3c9ed794");

        Log.e(TAG, "onCreate: " + ss.toString());
        Log.e(TAG, "httpFromJNI>>>>>>>>>>>>>" + s);
        tv.setText(b64 + "\n\n" + s);
    }

}
