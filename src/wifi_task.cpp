#include "wifi_task.h"

const char *ssid = "Padavan 2.4";
const char *password = "46684668";

void wifi_init()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    Serial.println();
}

uint8_t wifi_ceck()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}