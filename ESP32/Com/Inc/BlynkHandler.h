#ifndef BLYNK_HANDLER_H
#define BLYNK_HANDLER_H

#include <BlynkSimpleEsp32.h>
#include <WiFi.h>
#include <WiFiClient.h>

#define BLYNK_TEMPLATE_ID "TMPL6jbM2roF-"
#define BLYNK_TEMPLATE_NAME "ESP32"
#define BLYNK_AUTH_TOKEN "z_jRISyUJ_RliXmvZM0SEQgM64zhHVvJ"

#define LED_PIN 2

extern char ssid[];
extern char pass[];

extern BlynkTimer timer;

void setupBlynk();
void sendFakeSensorData();

#endif
