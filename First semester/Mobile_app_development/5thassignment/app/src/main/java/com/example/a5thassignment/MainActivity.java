package com.example.a5thassignment;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.OnSuccessListener;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.Calendar;

public class MainActivity extends AppCompatActivity {

//    @Override
//    protected void onCreate(Bundle savedInstanceState) {
//        super.onCreate(savedInstanceState);
//        setContentView(R.layout.activity_main);
//    }

    public void WriteInfotoFirebaseMultiNode (View view){
// Write a message to the database
// Write a message to the database
        FirebaseDatabase database = FirebaseDatabase.getInstance();
// Set path to get the multiple dropdown nodes
        DatabaseReference myRef = database.getReference("message/java/user");
        myRef.setValue("Hello, World! Time-date is "+ Calendar.getInstance().getTime());
//We can also use .child() to get the same results
        myRef = database.getReference("message1").child("java").child("user");
        myRef.setValue("Hello, World! Time-date is "+ Calendar.getInstance().getTime());
    }

    FirebaseDatabase database = FirebaseDatabase.getInstance();
    // getReference() gets the reference if the reference is already created...
// if reference is not created then it will create a new reference here
    DatabaseReference myRef = database.getReference("message");
    private static final String TAG=MainActivity.class.getSimpleName();
    TextView textView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        textView = (TextView) findViewById(R.id.textViewID);
// Read from the database
        myRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
// This method is called once with the initial value and again
// whenever data at this location is updated
                try{
                    String value = dataSnapshot.getValue(String.class);
                    Log.i(TAG, "Value is: " + value);
                    textView.setText(value);
                } catch (Exception exception){}
            }
            @Override
            public void onCancelled(DatabaseError error) {
// Failed to read value
                Log.i(TAG, "Failed to read value.", error.toException());
            }
        });
    }

    public void DeleteNode (View view){
        DatabaseReference dbNode =
                FirebaseDatabase.getInstance().getReference().getRoot().child("message1").child("java").
                        child("user");
        dbNode.setValue(null);
//or we can delete the node with the following code too
        DatabaseReference dbNodetwo =
                FirebaseDatabase.getInstance().getReference().getRoot()
                        .child("message");
        dbNodetwo.removeValue();
    }

    public void UpdateNode (View view){
        DatabaseReference reference = database.getReference().child("message");
        reference.setValue("Hello, World! Time-date is "+ Calendar.getInstance().getTime())
// we can also attach listener just to know whether it is successful or not
                .addOnSuccessListener(new OnSuccessListener<Void>() {
                    @Override
                    public void onSuccess(Void aVoid) {
// Write was successful!
                    }
                })
                .addOnFailureListener(new OnFailureListener() {
                    @Override
                    public void onFailure(@NonNull Exception e) {
// Write failed
                    }
                });
    }

}