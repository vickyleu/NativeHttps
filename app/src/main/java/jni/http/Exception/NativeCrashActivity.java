package jni.http.Exception;

import android.app.Activity;
import android.os.Bundle;


public class NativeCrashActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        throw (NativeError) getIntent().getSerializableExtra("error");
    }

}
