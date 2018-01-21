package zieln.com.myptrace;

import android.support.annotation.IntegerRes;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    TextView textView;
    Button button;
    Process p;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        textView = (TextView) findViewById(R.id.textView);
        button = (Button) findViewById(R.id.button);

        button.setOnClickListener(new View.OnClickListener(){

            @Override
            public void onClick(View v) {

                int ret = MyPtrace();
                textView.setText("MyPtrace return value: " + Integer.toString(ret));

            }
        });

        try{
            p = Runtime.getRuntime().exec("su");
            int suProcessRetval = p.waitFor();
            if(255 != suProcessRetval){
                Toast.makeText(this, "root priviligies granted", Toast.LENGTH_SHORT).show();
            }

        }catch(Exception e){
            Toast.makeText(this, "unable to grant root priviligies", Toast.LENGTH_SHORT).show();
        }
    }

    public native int MyPtrace();

    public native int getChildPid();

    static
    {
        System.loadLibrary("MyPtrace");
    }
}
