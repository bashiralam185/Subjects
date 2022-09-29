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
    private EditText Second_first;
    private EditText Second_second;
    private TextView secondQuestion;

    private Button mButtonAdd;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mEditText1 = findViewById(R.id.editTextNumberDecimal);
        mEditText2 = findViewById(R.id.editTextNumberDecimal2);
        mTextViewResult = findViewById(R.id.textView4);

        Second_first = findViewById(R.id.second_question1);
        secondQuestion = findViewById(R.id.second_ans);






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

                if (num1 == num2){
                    mTextViewResult.setText(String.valueOf("Both Are equal"));
                }
                else if ( num1 < num2){
                    mTextViewResult.setText(String.valueOf("A is less then B"));
                }
                else{
                    mTextViewResult.setText(String.valueOf("A is greater then B"));
                }





                int num3 = Integer.parseInt(Second_first.getText().toString());
                int i = 1;
                int k = 1;
                String s = "";
                while(k <  num3){
                    s = s + String.valueOf(i*i) + ' ';
                    i = i +1;
                    k = i* i;
                }
                secondQuestion.setText(String.valueOf(s));


            }
        });


    }
}

