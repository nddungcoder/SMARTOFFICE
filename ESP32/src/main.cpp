#define BLYNK_TEMPLATE_ID "TMPL6-Osyi-Jt"
#define BLYNK_TEMPLATE_NAME "SMARTOFFICE"
#define BLYNK_AUTH_TOKEN "eGmKDjog9NDM3ZWJm2D64h_IKj4l_iLV"

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "com.h"
#include "queue.h"
#include "message.h"
#include "device_manager.h"

#define LED_PIN 2

#define LUX_VPIN V0
#define GAS_VPIN V1
#define TEMP_VPIN V2
#define HUMI_VPIN V3
#define LED_VPIN V4
#define MOTOR_VPIN V7
#define AUTO_PIN V8

char ssid[] = "iPhone";
char pass[] = "68686868";

device_manager device;

FrameQueue txQueue;

BlynkTimer timer;

void initBlynk(void);
void updateBlynkData(void);

void initBlynk()
{
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void setup()
{
    Serial.begin(115200);

    Queue_init(&txQueue);

    // Khởi tạo kết nối UART và Blynk
    COM_Init();
    initBlynk();
    Serial.println("Connecting successfully!");

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW); // Tắt LED ban đầu

    timer.setInterval(3000L, updateBlynkData);
}

void loop()
{
    Blynk.run();
    timer.run();

    Transsmit_Handler(txQueue);
    Receive_Handler(device, txQueue);
}

void updateBlynkData()
{
    Blynk.virtualWrite(LUX_VPIN, device.getLdrLux());
    Blynk.virtualWrite(GAS_VPIN, device.getGasPPM());
    Blynk.virtualWrite(TEMP_VPIN, device.getDhtTemperature());
    Blynk.virtualWrite(HUMI_VPIN, device.getDhtHumidity());
    Blynk.virtualWrite(LED_VPIN, device.getLEDStatus());
    Blynk.virtualWrite(MOTOR_VPIN, device.getMotorSpeed());
    Blynk.virtualWrite(AUTO_PIN, device.getAutoMode());
}

BLYNK_WRITE(LED_VPIN)
{
    int value = param.asInt();
    device.setMotorSpeed(value);
    
    frame_message_t message;
    Create_Message_COMMAND(LED, (float)value, message);
    if(!full(&txQueue))
    {
        if (push(&txQueue, message, 10))
        {
            //TODO
        }
    } 
}

BLYNK_WRITE(MOTOR_VPIN)
{
    int value = param.asInt();
    device.setMotorSpeed(value);
    
    frame_message_t message;
    Create_Message_COMMAND(MOTOR, (float)value, message);
    if(!full(&txQueue))
    {
        if (push(&txQueue, message, 10))
        {
            //TODO
        }
    } 
}

BLYNK_WRITE(SIREN_VPIN)
{
    int value = param.asInt();
    device.setMotorSpeed(value);

    frame_message_t message;
    Create_Message_COMMAND(SIREN, (float)value, message);
    if(!full(&txQueue))
    {
        if (push(&txQueue, message, 10))
        {
            //TODO
        }
    } 
}

BLYNK_WRITE(AUTO_PIN)
{
    int value = param.asInt();
    device.setMotorSpeed(value);
    
    frame_message_t message;
    Create_Message_COMMAND(AUTO, (float)value, message);
    if(!full(&txQueue))
    {
        if (push(&txQueue, message, 10))
        {
            if(value == 1)
            {
                Serial.println("Auto mode enabled");
            }
            else
            {
                Serial.println("Auto mode disabled");
            }
        }
    }
}
