#include "global.h"

void rtc_init()
{
  if (!rtc.begin())
  {
    Serial.println("DS3231 not found");
  }
}

unsigned long timing, timing_2;
uint8_t dots_count;
String Hour_RTC, Minute_RTC, Second_RTC;

void printTime()
{

  if (millis() - timing > 500)
  {
    timing = millis();
    DateTime now = rtc.getTime();

    if (now.hour < 10)
    {
      Hour_RTC = "0" + String(now.hour);
    }
    else
    {
      Hour_RTC = String(now.hour);
    }

    if (now.minute < 10)
    {
      Minute_RTC = "0" + String(now.minute);
    }
    else
    {
      Minute_RTC = String(now.minute);
    }

    if (now.second < 10)
    {
      Second_RTC = "0" + String(now.second);
    }
    else
    {
      Second_RTC = String(now.second);
    }

    Display.setTextAlignment(PA_CENTER);

    dots_count++;

    if (dots_count == 2)
    {
      Display.print(Hour_RTC + ":" + Minute_RTC);
    }
    else if (dots_count == 4)
    {
      Display.print(Hour_RTC + " " + Minute_RTC);
      dots_count = 0;
    }

    Serial.println(Hour_RTC + ":" + Minute_RTC + ":" + Second_RTC);
  }
}

void printData()
{

  if (millis() - timing > 500)
  {
    timing = millis();

    Display.setTextAlignment(PA_CENTER);

    Display.print(rtc.getDateString().substring(0, 5));

    Serial.println(rtc.getDateString().substring(0, 5));
  }
}



void display_init()
{
  Display.begin();
  Display.setIntensity(3);
  Display.displayClear();
}

void ntp_time_init()
{
  timeClient.begin();
  timeClient.setTimeOffset(18000);
}

void setup()
{

  wifi_init();
  rtc_init();
  display_init();
  ntp_time_init();
  buzer_init();
}

int count;
bool data_flag, time_flag;
int brightnes;

uint8_t mode_display()
{
  if (millis() - timing_2 > 1000)
  {
    timing_2 = millis();
    count++;
    brightnes = map(analogRead(GPIO_NUM_34), 2000, 4095, 0, 10);
    // Display.setIntensity(brightnes);
    Serial.println(brightnes);
  }

  if (count < 20)
  {

    return 1;
  }
  if (count > 20)
  {
    printData();
  }
  if (count > 22)
  {
    count = 0;
    return 2;
  }
}

void display_task()
{
  switch (mode_display())
  {
  case 1:
    printTime();
    break;
  case 2:
    printData();
    break;

  default:
    break;
  }
}

bool check_wifi;
unsigned long check_wifi_count;
void loop()
{
  if (millis() - check_wifi_count > 10000)
  {
    check_wifi_count = millis();
    check_wifi = false;

    if (!wifi_ceck())
    {
      Serial.println("no connect");
    }
    else
    {
      Serial.println("connected");
    }

    check_wifi = true;
  }

  display_task();
}