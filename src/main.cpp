#include <Arduino.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <microDS3231.h>

MicroDS3231 rtc;

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

#define MAX_DEVICES 4
#define CLK_PIN 18
#define DATA_PIN 23
#define CS_PIN 5


MD_Parola Display = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

WiFiUDP ntpUDP;
// NTPClient timeClient(ntpUDP);

NTPClient timeClient(ntpUDP, "pool.ntp.org", 19800, 60000);

const char *ssid = "Padavan 2.4";
const char *password = "46684668";

String Time, hour, minute;
String Formatted_date;
long currentMillis = 0;
long previousMillis = 0;
int interval = 1000;

int flag_dots;




void obtainTime()
{

  timeClient.forceUpdate();

  Formatted_date = timeClient.getDay() + " ";
  Serial.println(Formatted_date);

  hour = timeClient.getFormattedTime().substring(0, 2);
  minute = timeClient.getFormattedTime().substring(3, 5);

  flag_dots++;

  if (flag_dots == 2)
  {
    Time = hour + " " + minute;
  }
  else if (flag_dots == 4)
  {
    Time = hour + ":" + minute;
    flag_dots = 0;
  }

  Serial.println(Time);
  Display.setTextAlignment(PA_CENTER);
  Display.print(Time);
  delay(500);
}

void rtc_init()
{
  // проверка наличия модуля на линии i2c
  if (!rtc.begin())
  {
    Serial.println("DS3231 not found");
  }

  // получаем все данные в структуру
  DateTime now = rtc.getTime();

  // меняем любой параметр
  //now.year += 5;
  // now.second;
  // now.minute;
  // now.hour;
  // now.day;
  // now.date;
  // now.month;

  // отправляем в rtc
  //rtc.setTime(now);

  //rtc.setTime(00, 38, 23, 18, 05, 2022);
  //rtc.setHMSDMY(HOUR, MIN, SEC, DAY, MONTH, YEAR);
}

unsigned long timing;
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
    else if(dots_count == 4)
    {
      Display.print(Hour_RTC + " " + Minute_RTC);
      dots_count = 0;
      
    }

    Serial.println(Hour_RTC + ":" + Minute_RTC + ":" + Second_RTC);

  }
  // получаем все данные в структуру и используем их
  // этот способ быстрее и "легче" вызова отдельных get-функций
  

  //       sprintf(HOUR_RTC, "%04d", number);
  // now.hour = 0 + now.hour;

  //   Serial.print(now.hour);
  // Serial.print(":");
  // Serial.print(now.minute);
  // Serial.print(":");
  // Serial.print(now.second);
  // Serial.print(" ");
  // Serial.print(now.day);
  // Serial.print(" ");
  // Serial.print(now.date);
  // Serial.print("/");
  // Serial.print(now.month);
  // Serial.print("/");
  // Serial.println(now.year);

}



void wifi_init()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Wi-Fi Connected");
}

void display_init()
{
  Display.begin();
  Display.setIntensity(0);
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
}

void loop()
{
  // obtainTime();

  // clock_tick();

  printTime();
  
}