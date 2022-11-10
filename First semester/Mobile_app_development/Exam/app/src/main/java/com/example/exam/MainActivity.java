package com.example.exam;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.text.method.ScrollingMovementMethod;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

//public class MainActivity extends AppCompatActivity {
//
//    EditText editText;
//    TextView textView;
//    public static final String EXTRA_MASSAGE = "com.example.exam";
//
//    @Override
//    protected void onCreate(Bundle savedInstanceState) {
//        super.onCreate(savedInstanceState);
//        setContentView(R.layout.activity_main);
////
////        editText = (EditText) findViewById(R.id.editTextTextPersonName);
////        textView = (TextView) findViewById(R.id.textView);
//        textView.setMovementMethod(new ScrollingMovementMethod());
//    }
//
//    public void sendMessage(View view) {
//
//        Intent intent = new Intent(this, DisplayMessageActivity.class);
//        String message = editText.getText().toString();
//        intent.putExtra(EXTRA_MASSAGE, message);
//        startActivity(intent);
//
//    }
//}


import android.content.Intent;
//import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
public class MainActivity extends AppCompatActivity {
    Button button;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        button = findViewById(R.id.btnOpenAct2);
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, DisplayMessageActivity.class);
                startActivity(intent);
            }
        });
    }
}