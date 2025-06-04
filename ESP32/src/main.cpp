#define BLYNK_TEMPLATE_ID "TMPL6-Osyi-Jt"
#define BLYNK_TEMPLATE_NAME "SMARTOFFICE"
#define BLYNK_AUTH_TOKEN "eGmKDjog9NDM3ZWJm2D64h_IKj4l_iLV"

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/uart.h"

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
#define MOTOR_VPIN V5
#define SIREN_VPIN V6
#define AUTO_PIN V8
#

char ssid[] = "P 504";
char pass[] = "12345679";

device_manager device;

FrameQueue txQueue;

BlynkTimer timer;

QueueHandle_t command_queue;
typedef struct
{
    ID_t type; // Loại thiết bị (LED, MOTOR, SIREN, AUTO)
    float value; 
} command_t;

void initBlynk(void);
void updateBlynkData(void);
void command_handler_task(void *param);

void initBlynk(void)
{
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    command_queue = xQueueCreate(10, sizeof(command_t));
    xTaskCreate(command_handler_task, "command_handler", 2048, NULL, 9, NULL);
}

void setup()
{
    Serial.begin(115200);

    Queue_init(&txQueue);

    // Khởi tạo kết nối UART và Blynk
    COM_Init();
    initBlynk();

    Serial.println("Connecting successfully!");

    timer.setInterval(3000L, updateBlynkData);
}

void loop()
{
    Blynk.run();
    timer.run();

    delay(100);
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

void command_handler_task(void *param)
{
    command_t cmd;
    while (1)
    {
        if (xQueueReceive(command_queue, &cmd, portMAX_DELAY))
        {
            // Cập nhật trạng thái thiết bị
            switch (cmd.type)
            {
            case LED:
                device.setLEDStatus(cmd.value);
                break;
            case MOTOR:
                device.setMotorSpeed(cmd.value);
                break;
            case SIREN:
                device.setSirenStatus(cmd.value);
                break;
            case AUTO:
                device.setAutoMode(cmd.value);
                break;
            default:
                break;
            }

            // Tạo frame gửi UART
            message_t message;
            Create_Message_COMMAND(cmd.type, cmd.value, message);

            // Đẩy vào hàng đợi txQueue
            if (!full(&txQueue))
            {
                push(&txQueue, message, 10);
            }
        }
    }
}

BLYNK_WRITE(LED_VPIN)
{
    command_t cmd = {.type = LED, .value = param.asInt()};
    xQueueSend(command_queue, &cmd, 0); // Không chặn
}

BLYNK_WRITE(MOTOR_VPIN)
{
    command_t cmd = {.type = MOTOR, .value = param.asInt()};
    xQueueSend(command_queue, &cmd, 0);
}

BLYNK_WRITE(SIREN_VPIN)
{
    command_t cmd = {.type = SIREN, .value = param.asInt()};
    xQueueSend(command_queue, &cmd, 0);
}

BLYNK_WRITE(AUTO_PIN)
{
    command_t cmd = {.type = AUTO, .value = param.asInt()};
    xQueueSend(command_queue, &cmd, 0);
}