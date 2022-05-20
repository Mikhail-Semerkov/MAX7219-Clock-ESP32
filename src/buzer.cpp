#include "buzer.h"

void buzer_init()
{
    tone(BUZZER_PIN, 2000, 200, BUZZER_CHANNEL);
    noTone(BUZZER_PIN, BUZZER_CHANNEL);
    delay(100);
    tone(BUZZER_PIN, 2000, 200, BUZZER_CHANNEL);
    noTone(BUZZER_PIN, BUZZER_CHANNEL);
    delay(100);
    tone(BUZZER_PIN, 2000, 200, BUZZER_CHANNEL);
    noTone(BUZZER_PIN, BUZZER_CHANNEL);
    delay(100);
}