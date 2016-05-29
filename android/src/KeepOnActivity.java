package com.kromophone;
public class KeepOnActivity extends org.qtproject.qt5.android.bindings.QtActivity {
    @Override
    public void onCreate(android.os.Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        this.getWindow().addFlags(android.view.WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
    }
}
