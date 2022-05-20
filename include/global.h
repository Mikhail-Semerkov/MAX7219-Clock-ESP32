#include <Arduino.h>
#include "wifi_task.h"
#include "buzer.h"




#include <microDS3231.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

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



String Time, hour, minute;

int flag_dots;