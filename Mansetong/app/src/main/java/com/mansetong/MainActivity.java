package com.mansetong;

import android.content.Intent;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.ibm.icu.util.Calendar;
import com.ibm.icu.util.ChineseCalendar;

public class MainActivity extends AppCompatActivity
{
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        String strResult = "陽";
        TextView tv = (TextView) findViewById(R.id.CalendarButton);

        // 현재 날짜 구하기
        Calendar calendar = Calendar.getInstance();
        ChineseCalendar chinaCal = new ChineseCalendar();
        chinaCal.setTimeInMillis(calendar.getTimeInMillis());

        // 년도 구하기
        int year = calendar.get(Calendar.YEAR);
        strResult += Integer.toString(year) + ".";
        // 월 구하기
        int month = calendar.get(Calendar.MONTH);
        strResult += Integer.toString(month + 1) + ".";
        // 일 구하기
        int date = calendar.get(Calendar.DAY_OF_MONTH);
        strResult += Integer.toString(date) + "  ";


        int chinaYY = chinaCal.get(ChineseCalendar.EXTENDED_YEAR) - 2637 ;
        int chinaMM = chinaCal.get(ChineseCalendar.MONTH) + 1;
        int chinaDD = chinaCal.get(ChineseCalendar.DAY_OF_MONTH);

        String chinaDate = "" ;     // 음력 날짜
        chinaDate += chinaYY ;      // 년
        chinaDate += "." ;          // 연도 구분자
        chinaDate += Integer.toString(chinaMM) ;
        chinaDate += "." ;          // 날짜 구분자
        chinaDate += Integer.toString(chinaDD) ;

        String[] weekDay = { "일요일", "월요일", "화요일", "수요일", "목요일", "금요일", "토요일" };
        int num = calendar.get(Calendar.DAY_OF_WEEK)-1;
        String today = weekDay[num];

        SetListenerOnUI();
        tv.setTextSize(20);
        tv.setText(strResult+"(陰"+chinaDate+")"+today+"\n\n庚癸壬丙\n" + "申酉辰申");
    }

    void SetListenerOnUI()
    {

        View calendarView = findViewById(R.id.CalendarButton);
        calendarView.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
               startActivity(new Intent(MainActivity.this, ManseCalendar.class));
            }

        });
        View daumCafe = findViewById(R.id.DaumCafe);
        daumCafe.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                startActivity(new Intent(Intent.ACTION_VIEW,Uri.parse("http://cafe.daum.net/nsaju")));
            }
        });
        View sajuStudy = findViewById(R.id.SajuStudy);
        sajuStudy.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                startActivity(new Intent(Intent.ACTION_VIEW,Uri.parse("http://sajuacademy.com/")));
            }
        });
    }
}
