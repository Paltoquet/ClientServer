package com.example.androidcl;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {


    private Button m_startAnimationButton;
    private Button m_stopAnimationButton;
    private Button m_sendButton;
    private EditText m_serverAddress;
    private EditText m_message;

    private String m_server;
    private String m_messagePrefix;
    private String m_messageData;
    private String m_startAnimation;
    private String m_stopAnimation;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        m_startAnimationButton = findViewById(R.id.startAnimation);
        m_stopAnimationButton = findViewById(R.id.stopAnimation);
        m_serverAddress = findViewById(R.id.serverAddress);
        m_sendButton = findViewById(R.id.sendButton);
        m_message = findViewById(R.id.message);

        m_server = "http://192.168.1.94:8080";
        m_messagePrefix = "obione";
        m_messageData = "coucoucouazoarr";
        m_startAnimation = "startAnimation";
        m_stopAnimation = "stopAnimation";

        m_serverAddress.addTextChangedListener(new TextWatcher() {

            @Override
            public void afterTextChanged(Editable s) {}

            @Override
            public void beforeTextChanged(CharSequence s, int start,
                                          int count, int after) {
            }

            @Override
            public void onTextChanged(CharSequence s, int start,
                                      int before, int count) {

                m_server = s.toString();
            }
        });

        m_message.addTextChangedListener(new TextWatcher() {

            @Override
            public void afterTextChanged(Editable s) {}

            @Override
            public void beforeTextChanged(CharSequence s, int start,
                                          int count, int after) {
            }

            @Override
            public void onTextChanged(CharSequence s, int start,
                                      int before, int count) {

                m_messageData = m_messagePrefix + s.toString();
            }
        });

        m_sendButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                ApiCall call = new ApiCall();
                call.execute(m_server, m_messageData);
            }
        });

        m_startAnimationButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                ApiCall call = new ApiCall();
                call.execute(m_server, m_startAnimation);
            }
        });

        m_stopAnimationButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                ApiCall call = new ApiCall();
                call.execute(m_server, m_stopAnimation);
            }
        });
    }
}
