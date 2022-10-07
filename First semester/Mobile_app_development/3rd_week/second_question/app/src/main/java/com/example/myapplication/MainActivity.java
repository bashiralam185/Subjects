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


    private EditText Last_Question1;
    private EditText last_Question2;
    private TextView last_Result;
    private TextView last_Result2;

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

        Last_Question1 = findViewById(R.id.last_question1);
        last_Question2 = findViewById(R.id.last_question2);
        last_Result = findViewById(R.id.last_result);
        last_Result2 = findViewById(R.id.last_result2);




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




                float n1;
                float n2;
                int res;
                int remainder;
                n1 = Float.parseFloat(Last_Question1.getText().toString());
                n2 = Float.parseFloat(last_Question2.getText().toString());
                if (n2 == 0){
                    last_Result.setText("Can't divide by 0!" );
                }
                else {
                    res = (int) ((int) n1 / n2);
                    remainder = (int) (n1 % n2);
                    last_Result.setText(String.valueOf(res)+", remainder " + String.valueOf(remainder) );
                }


            }
        });


    }
}

