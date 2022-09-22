package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private EditText mEditText1;
    private EditText mEditText2;
    private TextView mTextViewResult;
    private TextView mTextViewResult2;
    private Button mButtonAdd;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mEditText1 = findViewById(R.id.editTextNumberDecimal);
        mEditText2 = findViewById(R.id.editTextNumberDecimal2);
        mTextViewResult = findViewById(R.id.textView4);
        mTextViewResult2 = findViewById(R.id.textView6);


        mButtonAdd = findViewById(R.id.button);

        mButtonAdd.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (mEditText1.getText().toString().length() == 0) {
                    mEditText1.setText("0");
                }

                if (mEditText2.getText().toString().length() == 0) {
                    mEditText2.setText("0");
                }


                int num1 = Integer.parseInt(mEditText1.getText().toString());
                int num2 = Integer.parseInt(mEditText2.getText().toString());

                int area = num1 * num2;
                int area2 =( num1 + num2)*2;

                mTextViewResult.setText(String.valueOf(area));
                mTextViewResult2.setText(String.valueOf(area2));
            }
        });


    }
}

