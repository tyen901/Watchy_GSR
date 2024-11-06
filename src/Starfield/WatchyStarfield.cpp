#include "WatchyStarfield.h"

// DARKMODE
// #define DARKMODE false

// HOUR_SET, change it to 12 to switch to 12-hour
// #define HOUR_SET 24

// change it to your location
// latitude, longitude, timezone
// Currently set to Wellington, NZ
#define LOC -41.28664, 174.77557, 13

RTC_DATA_ATTR bool DARKMODE = false;
RTC_DATA_ATTR bool HOUR_SET = true;

moonPhaser moonP;

void WatchyStarfield::handleButtonPress(uint8_t SwitchNumber)
{
    switch (SwitchNumber)
    {
    case 2: // Back
        HOUR_SET = !HOUR_SET;
        break;
    case 3: // Up
        HOUR_SET = !HOUR_SET;
        break;
    case 4: // Down
        DARKMODE = !DARKMODE;
        break;
    }
}

void WatchyStarfield::drawWatchFace()
{
    WatchyGSR watchyGSR;

    WatchyGSR::display.fillScreen(DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
    WatchyGSR::display.setTextColor(DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    
    drawField();
    drawTime();
    drawDate();
    drawSteps();
    drawBattery();

    bool isWifiConnected = watchyGSR.WiFiStatus() == WL_CONNECTED;
    
    WatchyGSR::display.drawBitmap(118, 168, isWifiConnected ? wifi : wifioff, 25, 18, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    drawMoon();
    drawSun();
}

void WatchyStarfield::drawTime()
{
    WatchyGSR::display.setFont(&DSEG7_Classic_Bold_53);
    WatchyGSR::display.setCursor(6, 53 + 5);
    // int displayHour;
    // if(HOUR_SET==12)
    // {
    //     displayHour = ((WatchTime.Local.Hour+11)%12)+1;
    // }
    // else
    // {
    //     displayHour = WatchTime.Local.Hour;
    // }
    // if(displayHour < 10)
    // {
    //     WatchyGSR::display.print("0");
    // }
    // WatchyGSR::display.print(displayHour);
    // WatchyGSR::display.print(":");
    // if(WatchTime.Local.Minute < 10)
    // {
    //     WatchyGSR::display.print("0");
    // }
    // WatchyGSR::display.println(WatchTime.Local.Minute);
    long ss = WatchTime.Local.Hour * 60 + WatchTime.Local.Minute;
    int sh = ss / 60;

    if (HOUR_SET == false && sh >= 12)
    {
        WatchyGSR::display.fillRect(7, 60, 25, 9, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
        WatchyGSR::display.drawBitmap(7, 60, pm, 25, 9, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }
    else if (HOUR_SET == false && sh < 12)
    {
        WatchyGSR::display.fillRect(7, 60, 25, 9, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
        WatchyGSR::display.drawBitmap(7, 60, am, 25, 9, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }

    if (HOUR_SET == false && sh > 12)
    {
        sh -= 12;
    }
    int sm = ss % 60;
    int a = sh >= 10 ? sh / 10 : 0;
    int b = sh % 10;
    int c = sm >= 10 ? sm / 10 : 0;
    int d = sm % 10;

    if (a == 0)
        WatchyGSR::display.drawBitmap(11, 5, fd_0, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 1)
        WatchyGSR::display.drawBitmap(11, 5, fd_1, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 2)
        WatchyGSR::display.drawBitmap(11, 5, fd_2, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 3)
        WatchyGSR::display.drawBitmap(11, 5, fd_3, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 4)
        WatchyGSR::display.drawBitmap(11, 5, fd_4, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 5)
        WatchyGSR::display.drawBitmap(11, 5, fd_5, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 6)
        WatchyGSR::display.drawBitmap(11, 5, fd_6, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 7)
        WatchyGSR::display.drawBitmap(11, 5, fd_7, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 8)
        WatchyGSR::display.drawBitmap(11, 5, fd_8, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 9)
        WatchyGSR::display.drawBitmap(11, 5, fd_9, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (b == 0)
        WatchyGSR::display.drawBitmap(55, 5, fd_0, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 1)
        WatchyGSR::display.drawBitmap(55, 5, fd_1, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 2)
        WatchyGSR::display.drawBitmap(55, 5, fd_2, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 3)
        WatchyGSR::display.drawBitmap(55, 5, fd_3, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 4)
        WatchyGSR::display.drawBitmap(55, 5, fd_4, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 5)
        WatchyGSR::display.drawBitmap(55, 5, fd_5, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 6)
        WatchyGSR::display.drawBitmap(55, 5, fd_6, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 7)
        WatchyGSR::display.drawBitmap(55, 5, fd_7, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 8)
        WatchyGSR::display.drawBitmap(55, 5, fd_8, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 9)
        WatchyGSR::display.drawBitmap(55, 5, fd_9, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (c == 0)
        WatchyGSR::display.drawBitmap(111, 5, fd_0, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 1)
        WatchyGSR::display.drawBitmap(111, 5, fd_1, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 2)
        WatchyGSR::display.drawBitmap(111, 5, fd_2, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 3)
        WatchyGSR::display.drawBitmap(111, 5, fd_3, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 4)
        WatchyGSR::display.drawBitmap(111, 5, fd_4, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 5)
        WatchyGSR::display.drawBitmap(111, 5, fd_5, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 6)
        WatchyGSR::display.drawBitmap(111, 5, fd_6, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 7)
        WatchyGSR::display.drawBitmap(111, 5, fd_7, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 8)
        WatchyGSR::display.drawBitmap(111, 5, fd_8, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 9)
        WatchyGSR::display.drawBitmap(111, 5, fd_9, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (d == 0)
        WatchyGSR::display.drawBitmap(155, 5, fd_0, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 1)
        WatchyGSR::display.drawBitmap(155, 5, fd_1, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 2)
        WatchyGSR::display.drawBitmap(155, 5, fd_2, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 3)
        WatchyGSR::display.drawBitmap(155, 5, fd_3, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 4)
        WatchyGSR::display.drawBitmap(155, 5, fd_4, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 5)
        WatchyGSR::display.drawBitmap(155, 5, fd_5, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 6)
        WatchyGSR::display.drawBitmap(155, 5, fd_6, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 7)
        WatchyGSR::display.drawBitmap(155, 5, fd_7, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 8)
        WatchyGSR::display.drawBitmap(155, 5, fd_8, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 9)
        WatchyGSR::display.drawBitmap(155, 5, fd_9, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
}

void WatchyStarfield::drawDate()
{
    WatchyGSR::display.setFont(&Seven_Segment10pt7b);

    int16_t x1, y1;
    uint16_t w, h;

    String dayOfWeek = dayStr(WatchTime.Local.Wday);
    dayOfWeek = dayOfWeek.substring(0, dayOfWeek.length() - 3);
    WatchyGSR::display.getTextBounds(dayOfWeek, 5, 85, &x1, &y1, &w, &h);
    if (WatchTime.Local.Wday == 4)
    {
        w = w - 5;
    }
    WatchyGSR::display.setCursor(76 - w, 86);
    WatchyGSR::display.println(dayOfWeek);

    String month = monthShortStr(WatchTime.Local.Month);
    WatchyGSR::display.getTextBounds(month, 60, 110, &x1, &y1, &w, &h);
    WatchyGSR::display.setCursor(79 - w, 110);
    WatchyGSR::display.println(month);

    // WatchyGSR::display.setFont(&DSEG7_Classic_Bold_25);
    // WatchyGSR::display.setCursor(6, 120);
    // if(WatchTime.Local.Day < 10)
    // {
    // WatchyGSR::display.print("0");
    // }
    // WatchyGSR::display.println(WatchTime.Local.Day);
    // WatchyGSR::display.setCursor(6, 154);
    // WatchyGSR::display.println(tmYearToCalendar(WatchTime.Local.Year));// offset from 1970, since year is stored in uint8_t

    int da = WatchTime.Local.Day;
    int year = WatchTime.Local.Year + WatchyGSR::SRTC.getLocalYearOffset();

    int a = da / 10;
    int b = da % 10;
    int c = year / 1000;
    year = year % 1000;
    int d = year / 100;
    year = year % 100;
    int e = year / 10;
    year = year % 10;
    int f = year;

    if (a == 0)
        WatchyGSR::display.drawBitmap(8, 95, dd_0, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 1)
        WatchyGSR::display.drawBitmap(8, 95, dd_1, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 2)
        WatchyGSR::display.drawBitmap(8, 95, dd_2, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 3)
        WatchyGSR::display.drawBitmap(8, 95, dd_3, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 4)
        WatchyGSR::display.drawBitmap(8, 95, dd_4, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 5)
        WatchyGSR::display.drawBitmap(8, 95, dd_5, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 6)
        WatchyGSR::display.drawBitmap(8, 95, dd_6, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 7)
        WatchyGSR::display.drawBitmap(8, 95, dd_7, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 8)
        WatchyGSR::display.drawBitmap(8, 95, dd_8, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 9)
        WatchyGSR::display.drawBitmap(8, 95, dd_9, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (b == 0)
        WatchyGSR::display.drawBitmap(29, 95, dd_0, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 1)
        WatchyGSR::display.drawBitmap(29, 95, dd_1, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 2)
        WatchyGSR::display.drawBitmap(29, 95, dd_2, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 3)
        WatchyGSR::display.drawBitmap(29, 95, dd_3, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 4)
        WatchyGSR::display.drawBitmap(29, 95, dd_4, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 5)
        WatchyGSR::display.drawBitmap(29, 95, dd_5, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 6)
        WatchyGSR::display.drawBitmap(29, 95, dd_6, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 7)
        WatchyGSR::display.drawBitmap(29, 95, dd_7, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 8)
        WatchyGSR::display.drawBitmap(29, 95, dd_8, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 9)
        WatchyGSR::display.drawBitmap(29, 95, dd_9, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (c == 0)
        WatchyGSR::display.drawBitmap(8, 129, dd_0, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 1)
        WatchyGSR::display.drawBitmap(8, 129, dd_1, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 2)
        WatchyGSR::display.drawBitmap(8, 129, dd_2, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 3)
        WatchyGSR::display.drawBitmap(8, 129, dd_3, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 4)
        WatchyGSR::display.drawBitmap(8, 129, dd_4, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 5)
        WatchyGSR::display.drawBitmap(8, 129, dd_5, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 6)
        WatchyGSR::display.drawBitmap(8, 129, dd_6, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 7)
        WatchyGSR::display.drawBitmap(8, 129, dd_7, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 8)
        WatchyGSR::display.drawBitmap(8, 129, dd_8, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 9)
        WatchyGSR::display.drawBitmap(8, 129, dd_9, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (d == 0)
        WatchyGSR::display.drawBitmap(29, 129, dd_0, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 1)
        WatchyGSR::display.drawBitmap(29, 129, dd_1, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 2)
        WatchyGSR::display.drawBitmap(29, 129, dd_2, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 3)
        WatchyGSR::display.drawBitmap(29, 129, dd_3, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 4)
        WatchyGSR::display.drawBitmap(29, 129, dd_4, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 5)
        WatchyGSR::display.drawBitmap(29, 129, dd_5, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 6)
        WatchyGSR::display.drawBitmap(29, 129, dd_6, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 7)
        WatchyGSR::display.drawBitmap(29, 129, dd_7, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 8)
        WatchyGSR::display.drawBitmap(29, 129, dd_8, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 9)
        WatchyGSR::display.drawBitmap(29, 129, dd_9, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (e == 0)
        WatchyGSR::display.drawBitmap(50, 129, dd_0, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 1)
        WatchyGSR::display.drawBitmap(50, 129, dd_1, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 2)
        WatchyGSR::display.drawBitmap(50, 129, dd_2, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 3)
        WatchyGSR::display.drawBitmap(50, 129, dd_3, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 4)
        WatchyGSR::display.drawBitmap(50, 129, dd_4, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 5)
        WatchyGSR::display.drawBitmap(50, 129, dd_5, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 6)
        WatchyGSR::display.drawBitmap(50, 129, dd_6, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 7)
        WatchyGSR::display.drawBitmap(50, 129, dd_7, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 8)
        WatchyGSR::display.drawBitmap(50, 129, dd_8, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 9)
        WatchyGSR::display.drawBitmap(50, 129, dd_9, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (f == 0)
        WatchyGSR::display.drawBitmap(71, 129, dd_0, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 1)
        WatchyGSR::display.drawBitmap(71, 129, dd_1, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 2)
        WatchyGSR::display.drawBitmap(71, 129, dd_2, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 3)
        WatchyGSR::display.drawBitmap(71, 129, dd_3, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 4)
        WatchyGSR::display.drawBitmap(71, 129, dd_4, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 5)
        WatchyGSR::display.drawBitmap(71, 129, dd_5, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 6)
        WatchyGSR::display.drawBitmap(71, 129, dd_6, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 7)
        WatchyGSR::display.drawBitmap(71, 129, dd_7, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 8)
        WatchyGSR::display.drawBitmap(71, 129, dd_8, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 9)
        WatchyGSR::display.drawBitmap(71, 129, dd_9, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
}

void WatchyStarfield::drawSteps()
{
    // reset step counter at midnight
    if (WatchTime.Local.Hour == 0 && WatchTime.Local.Minute == 0)
    {
        // st4 = st3;
        // st3 = st2;
        // st2 = st1;
        // st1 = stepCount;
        //TODO : FIX THIS
        //sensor.resetStepCounter();
        // stepCount = 0;
    }
    WatchyGSR watchyGSR;
    uint32_t stepCount = watchyGSR.CurrentStepCount();

    // WatchyGSR::display.drawBitmap(10, 165, steps, 19, 23, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    // WatchyGSR::display.setCursor(6, 190);
    // if (stepCount >= 10000)
    //     ;
    // else if (stepCount >= 1000)
    //     WatchyGSR::display.print("0");
    // else if (stepCount >= 100)
    //     WatchyGSR::display.print("00");
    // else if (stepCount >= 10)
    //     WatchyGSR::display.print("000");
    // else if (stepCount >= 0)
    //     WatchyGSR::display.print("0000");
    // WatchyGSR::display.println(stepCount);

    // uint32_t l1 = 61 * st1 / 20000;
    // uint32_t l2 = 61 * st2 / 20000;
    // uint32_t l3 = 61 * st3 / 20000;
    // uint32_t l4 = 61 * st4 / 20000;
    uint32_t l5 = 61 * stepCount / 10000;

    if (l5 > 61)
    {
        l5 = 61;
    }

    // WatchyGSR::display.fillRect(125, 73 + 61 - l1, 9, l4, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    // WatchyGSR::display.fillRect(143, 73 + 61 - l1, 9, l3, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    // WatchyGSR::display.fillRect(161, 73 + 61 - l1, 9, l2, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    // WatchyGSR::display.fillRect(179, 73 + 61 - l1, 9, l1, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    WatchyGSR::display.fillRect(131, 148, l5, 9, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    // WatchyGSR::display.

    int a = stepCount / 10000;
    stepCount = stepCount % 10000;
    int b = stepCount / 1000;
    stepCount = stepCount % 1000;
    int c = stepCount / 100;
    stepCount = stepCount % 100;
    int d = stepCount / 10;
    int e = stepCount % 10;

    if (a == 0)
        WatchyGSR::display.drawBitmap(8, 165, dd_0, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 1)
        WatchyGSR::display.drawBitmap(8, 165, dd_1, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 2)
        WatchyGSR::display.drawBitmap(8, 165, dd_2, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 3)
        WatchyGSR::display.drawBitmap(8, 165, dd_3, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 4)
        WatchyGSR::display.drawBitmap(8, 165, dd_4, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 5)
        WatchyGSR::display.drawBitmap(8, 165, dd_5, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 6)
        WatchyGSR::display.drawBitmap(8, 165, dd_6, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 7)
        WatchyGSR::display.drawBitmap(8, 165, dd_7, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 8)
        WatchyGSR::display.drawBitmap(8, 165, dd_8, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 9)
        WatchyGSR::display.drawBitmap(8, 165, dd_9, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (b == 0)
        WatchyGSR::display.drawBitmap(29, 165, dd_0, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 1)
        WatchyGSR::display.drawBitmap(29, 165, dd_1, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 2)
        WatchyGSR::display.drawBitmap(29, 165, dd_2, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 3)
        WatchyGSR::display.drawBitmap(29, 165, dd_3, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 4)
        WatchyGSR::display.drawBitmap(29, 165, dd_4, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 5)
        WatchyGSR::display.drawBitmap(29, 165, dd_5, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 6)
        WatchyGSR::display.drawBitmap(29, 165, dd_6, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 7)
        WatchyGSR::display.drawBitmap(29, 165, dd_7, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 8)
        WatchyGSR::display.drawBitmap(29, 165, dd_8, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 9)
        WatchyGSR::display.drawBitmap(29, 165, dd_9, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (c == 0)
        WatchyGSR::display.drawBitmap(50, 165, dd_0, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 1)
        WatchyGSR::display.drawBitmap(50, 165, dd_1, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 2)
        WatchyGSR::display.drawBitmap(50, 165, dd_2, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 3)
        WatchyGSR::display.drawBitmap(50, 165, dd_3, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 4)
        WatchyGSR::display.drawBitmap(50, 165, dd_4, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 5)
        WatchyGSR::display.drawBitmap(50, 165, dd_5, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 6)
        WatchyGSR::display.drawBitmap(50, 165, dd_6, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 7)
        WatchyGSR::display.drawBitmap(50, 165, dd_7, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 8)
        WatchyGSR::display.drawBitmap(50, 165, dd_8, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 9)
        WatchyGSR::display.drawBitmap(50, 165, dd_9, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (d == 0)
        WatchyGSR::display.drawBitmap(71, 165, dd_0, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 1)
        WatchyGSR::display.drawBitmap(71, 165, dd_1, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 2)
        WatchyGSR::display.drawBitmap(71, 165, dd_2, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 3)
        WatchyGSR::display.drawBitmap(71, 165, dd_3, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 4)
        WatchyGSR::display.drawBitmap(71, 165, dd_4, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 5)
        WatchyGSR::display.drawBitmap(71, 165, dd_5, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 6)
        WatchyGSR::display.drawBitmap(71, 165, dd_6, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 7)
        WatchyGSR::display.drawBitmap(71, 165, dd_7, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 8)
        WatchyGSR::display.drawBitmap(71, 165, dd_8, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 9)
        WatchyGSR::display.drawBitmap(71, 165, dd_9, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (e == 0)
        WatchyGSR::display.drawBitmap(92, 165, dd_0, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 1)
        WatchyGSR::display.drawBitmap(92, 165, dd_1, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 2)
        WatchyGSR::display.drawBitmap(92, 165, dd_2, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 3)
        WatchyGSR::display.drawBitmap(92, 165, dd_3, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 4)
        WatchyGSR::display.drawBitmap(92, 165, dd_4, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 5)
        WatchyGSR::display.drawBitmap(92, 165, dd_5, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 6)
        WatchyGSR::display.drawBitmap(92, 165, dd_6, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 7)
        WatchyGSR::display.drawBitmap(92, 165, dd_7, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 8)
        WatchyGSR::display.drawBitmap(92, 165, dd_8, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 9)
        WatchyGSR::display.drawBitmap(92, 165, dd_9, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
}

int mapBatteryLevel(float voltage, float minVoltage, float maxVoltage, int minLevel, int maxLevel)
{
    if (voltage <= minVoltage)
    {
        return minLevel;
    }
    else if (voltage >= maxVoltage)
    {
        return maxLevel;
    }
    else
    {
        return (int)((voltage - minVoltage) * (maxLevel - minLevel) / (maxVoltage - minVoltage) + minLevel);
    }
}

void WatchyStarfield::drawBattery()
{
    float VBAT = WatchyGSR::getBatteryVoltage();
    int maxWidth = 37;

#ifdef ARDUINO_ESP32S3_DEV
    float MaxVBAT = 3.9;
    float MinVBAT = 3.6;
#else
    float MaxVBAT = 4.1;
    float MinVBAT = 3.8;
#endif

    int batteryLevel = mapBatteryLevel(VBAT, MinVBAT, MaxVBAT, 0, maxWidth);

    WatchyGSR::display.fillRect(155, 169, batteryLevel, 15, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
}

void WatchyStarfield::drawField()
{
    WatchyGSR::display.drawBitmap(0, 0, field, 200, 200, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
}

void WatchyStarfield::drawMoon()
{
    moonData_t moon; // variable to receive the data

    int year = WatchTime.Local.Year + WatchyGSR::SRTC.getLocalYearOffset();
    int32_t month = WatchTime.Local.Month;
    int32_t day = WatchTime.Local.Day;
    double hour = WatchTime.Local.Hour + 0.1;

    moon = moonP.getPhase(year, month, day, hour);

    int ag = moon.angle;
    double lt = moon.percentLit;

    // Waxing: 0-180
    // Waning: 180-360
    // WatchyGSR::display.setCursor(100, 74);

    if (ag <= 180)
    {
        if (lt < 0.1)
            WatchyGSR::display.drawBitmap(131, 74, luna1, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.25)
            WatchyGSR::display.drawBitmap(131, 74, luna12, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.4)
            WatchyGSR::display.drawBitmap(131, 74, luna11, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.6)
            WatchyGSR::display.drawBitmap(131, 74, luna10, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.75)
            WatchyGSR::display.drawBitmap(131, 74, luna9, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.9)
            WatchyGSR::display.drawBitmap(131, 74, luna8, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        else
            WatchyGSR::display.drawBitmap(131, 74, luna7, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }
    else
    {
        if (lt < 0.1)
            WatchyGSR::display.drawBitmap(131, 74, luna1, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.25)
            WatchyGSR::display.drawBitmap(131, 74, luna2, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.4)
            WatchyGSR::display.drawBitmap(131, 74, luna3, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.6)
            WatchyGSR::display.drawBitmap(131, 74, luna4, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.75)
            WatchyGSR::display.drawBitmap(131, 74, luna5, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.9)
            WatchyGSR::display.drawBitmap(131, 74, luna6, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        else
            WatchyGSR::display.drawBitmap(131, 74, luna7, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }

    // WatchyGSR::display.print(year);
    // // WatchyGSR::display.print(moon.angle);
    // WatchyGSR::display.setCursor(100, 100);
    // // WatchyGSR::display.print(moon.percentLit);
    // WatchyGSR::display.print(month);

    // WatchyGSR::display.setCursor(100, 130);
    // WatchyGSR::display.print(day);
    //  Serial.print( "Moon phase angle: " );
    //  Serial.print( moon.angle );             // angle is a integer between 0-360
    //  Serial.println( " degrees." );
    //  Serial.print( "Moon surface lit: " );
    //  Serial.println( moon.percentLit * 100 );  // percentLit is a real between 0-1
}

void WatchyStarfield::drawSun()
{
    Dusk2Dawn location(LOC);
    int year = WatchTime.Local.Year + WatchyGSR::SRTC.getLocalYearOffset();
    int32_t month = WatchTime.Local.Month;
    int32_t day = WatchTime.Local.Day;
    int sr = location.sunrise(year, month, day, false);
    int ss = location.sunset(year, month, day, false);

    long k = WatchTime.Local.Hour * 60 + WatchTime.Local.Minute;
    int tk = (k - sr) * 60 / (ss - sr);
    if (k > ss)
        tk = 60;
    else if (k < sr)
        tk = 0;
    WatchyGSR::display.drawBitmap(110, 132 - tk, arr, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    int rh = sr / 60;
    int rm = sr % 60;
    int sh = ss / 60;
    int sm = ss % 60;

    if (HOUR_SET == false && rh > 12)
    {
        rh -= 12;
    }

    if (HOUR_SET == false && sh > 12)
    {
        sh -= 12;
    }

    int a = sh >= 10 ? sh / 10 : 0;
    int b = sh % 10;
    int c = sm >= 10 ? sm / 10 : 0;
    int d = sm % 10;
    int e = rh >= 10 ? rh / 10 : 0;
    int f = rh % 10;
    int g = rm >= 10 ? rm / 10 : 0;
    int h = rm % 10;

    if (a == 0)
        WatchyGSR::display.drawBitmap(116, 67, num_0, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 1)
        WatchyGSR::display.drawBitmap(116, 67, num_1, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 2)
        WatchyGSR::display.drawBitmap(116, 67, num_2, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 3)
        WatchyGSR::display.drawBitmap(116, 67, num_3, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 4)
        WatchyGSR::display.drawBitmap(116, 67, num_4, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 5)
        WatchyGSR::display.drawBitmap(116, 67, num_5, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 6)
        WatchyGSR::display.drawBitmap(116, 67, num_6, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 7)
        WatchyGSR::display.drawBitmap(116, 67, num_7, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 8)
        WatchyGSR::display.drawBitmap(116, 67, num_8, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 9)
        WatchyGSR::display.drawBitmap(116, 67, num_9, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (b == 0)
        WatchyGSR::display.drawBitmap(120, 67, num_0, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 1)
        WatchyGSR::display.drawBitmap(120, 67, num_1, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 2)
        WatchyGSR::display.drawBitmap(120, 67, num_2, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 3)
        WatchyGSR::display.drawBitmap(120, 67, num_3, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 4)
        WatchyGSR::display.drawBitmap(120, 67, num_4, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 5)
        WatchyGSR::display.drawBitmap(120, 67, num_5, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 6)
        WatchyGSR::display.drawBitmap(120, 67, num_6, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 7)
        WatchyGSR::display.drawBitmap(120, 67, num_7, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 8)
        WatchyGSR::display.drawBitmap(120, 67, num_8, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 9)
        WatchyGSR::display.drawBitmap(120, 67, num_9, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (c == 0)
        WatchyGSR::display.drawBitmap(128, 67, num_0, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 1)
        WatchyGSR::display.drawBitmap(128, 67, num_1, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 2)
        WatchyGSR::display.drawBitmap(128, 67, num_2, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 3)
        WatchyGSR::display.drawBitmap(128, 67, num_3, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 4)
        WatchyGSR::display.drawBitmap(128, 67, num_4, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 5)
        WatchyGSR::display.drawBitmap(128, 67, num_5, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 6)
        WatchyGSR::display.drawBitmap(128, 67, num_6, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 7)
        WatchyGSR::display.drawBitmap(128, 67, num_7, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 8)
        WatchyGSR::display.drawBitmap(128, 67, num_8, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 9)
        WatchyGSR::display.drawBitmap(128, 67, num_9, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (d == 0)
        WatchyGSR::display.drawBitmap(132, 67, num_0, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 1)
        WatchyGSR::display.drawBitmap(132, 67, num_1, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 2)
        WatchyGSR::display.drawBitmap(132, 67, num_2, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 3)
        WatchyGSR::display.drawBitmap(132, 67, num_3, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 4)
        WatchyGSR::display.drawBitmap(132, 67, num_4, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 5)
        WatchyGSR::display.drawBitmap(132, 67, num_5, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 6)
        WatchyGSR::display.drawBitmap(132, 67, num_6, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 7)
        WatchyGSR::display.drawBitmap(132, 67, num_7, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 8)
        WatchyGSR::display.drawBitmap(132, 67, num_8, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 9)
        WatchyGSR::display.drawBitmap(132, 67, num_9, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (e == 0)
        WatchyGSR::display.drawBitmap(116, 137, num_0, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 1)
        WatchyGSR::display.drawBitmap(116, 137, num_1, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 2)
        WatchyGSR::display.drawBitmap(116, 137, num_2, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 3)
        WatchyGSR::display.drawBitmap(116, 137, num_3, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 4)
        WatchyGSR::display.drawBitmap(116, 137, num_4, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 5)
        WatchyGSR::display.drawBitmap(116, 137, num_5, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 6)
        WatchyGSR::display.drawBitmap(116, 137, num_6, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 7)
        WatchyGSR::display.drawBitmap(116, 137, num_7, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 8)
        WatchyGSR::display.drawBitmap(116, 137, num_8, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 9)
        WatchyGSR::display.drawBitmap(116, 137, num_9, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (f == 0)
        WatchyGSR::display.drawBitmap(120, 137, num_0, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 1)
        WatchyGSR::display.drawBitmap(120, 137, num_1, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 2)
        WatchyGSR::display.drawBitmap(120, 137, num_2, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 3)
        WatchyGSR::display.drawBitmap(120, 137, num_3, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 4)
        WatchyGSR::display.drawBitmap(120, 137, num_4, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 5)
        WatchyGSR::display.drawBitmap(120, 137, num_5, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 6)
        WatchyGSR::display.drawBitmap(120, 137, num_6, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 7)
        WatchyGSR::display.drawBitmap(120, 137, num_7, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 8)
        WatchyGSR::display.drawBitmap(120, 137, num_8, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 9)
        WatchyGSR::display.drawBitmap(120, 137, num_9, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (g == 0)
        WatchyGSR::display.drawBitmap(128, 137, num_0, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 1)
        WatchyGSR::display.drawBitmap(128, 137, num_1, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 2)
        WatchyGSR::display.drawBitmap(128, 137, num_2, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 3)
        WatchyGSR::display.drawBitmap(128, 137, num_3, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 4)
        WatchyGSR::display.drawBitmap(128, 137, num_4, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 5)
        WatchyGSR::display.drawBitmap(128, 137, num_5, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 6)
        WatchyGSR::display.drawBitmap(128, 137, num_6, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 7)
        WatchyGSR::display.drawBitmap(128, 137, num_7, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 8)
        WatchyGSR::display.drawBitmap(128, 137, num_8, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 9)
        WatchyGSR::display.drawBitmap(128, 137, num_9, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (h == 0)
        WatchyGSR::display.drawBitmap(132, 137, num_0, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 1)
        WatchyGSR::display.drawBitmap(132, 137, num_1, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 2)
        WatchyGSR::display.drawBitmap(132, 137, num_2, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 3)
        WatchyGSR::display.drawBitmap(132, 137, num_3, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 4)
        WatchyGSR::display.drawBitmap(132, 137, num_4, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 5)
        WatchyGSR::display.drawBitmap(132, 137, num_5, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 6)
        WatchyGSR::display.drawBitmap(132, 137, num_6, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 7)
        WatchyGSR::display.drawBitmap(132, 137, num_7, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 8)
        WatchyGSR::display.drawBitmap(132, 137, num_8, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 9)
        WatchyGSR::display.drawBitmap(132, 137, num_9, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
}