#define BLYNK_TEMPLATE_NAME "SMARTOFFICE"
#define BLYNK_TEMPLATE_ID "TMPL6-Osyi-Jt"
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
    COM_Init(115200);
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

#define EPSILON 0.01f  

bool isDifferent(float a, float b) {
    return fabs(a - b) > EPSILON;
}

void updateBlynkData()
{
    static float last_lux = -1, last_gas = -1, last_temp = -1, last_humi = -1;
    static float last_led = -1, last_motor = -1, last_auto = -1;

    float lux = device.getLdrLux();
    float gas = device.getGasPPM();
    float temp = device.getDhtTemperature();
    float humi = device.getDhtHumidity();
    float led = device.getLEDStatus();
    float motor = device.getMotorSpeed();
    float autoMode = device.getAutoMode();

    if (isDifferent(lux, last_lux)) {
        Blynk.virtualWrite(LUX_VPIN, lux);
        last_lux = lux;
    }

    if (isDifferent(gas, last_gas)) {
        Blynk.virtualWrite(GAS_VPIN, gas);
        last_gas = gas;
    }

    if (isDifferent(temp, last_temp)) {
        Blynk.virtualWrite(TEMP_VPIN, temp);
        last_temp = temp;
    }

    if (isDifferent(humi, last_humi)) {
        Blynk.virtualWrite(HUMI_VPIN, humi);
        last_humi = humi;
    }

    if (isDifferent(led, last_led)) {
        Blynk.virtualWrite(LED_VPIN, led);
        last_led = led;
    }

    if (isDifferent(motor, last_motor)) {
        Blynk.virtualWrite(MOTOR_VPIN, motor);
        last_motor = motor;
    }

    if (isDifferent(autoMode, last_auto)) {
        Blynk.virtualWrite(AUTO_PIN, autoMode);
        last_auto = autoMode;
    }
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
            Create_Message_COMMAND(cmd.type, cmd.value, &message);

            // Đẩy vào hàng đợi txQueue
            if (!full(&txQueue))
            {
                push(&txQueue, &message, 10);
            }
        }
    }
}

void resetBlynkWidgetsToDefault() {
    Blynk.virtualWrite(LED_VPIN, 0);     
    Blynk.virtualWrite(MOTOR_VPIN, 0);  
    Blynk.virtualWrite(SIREN_VPIN, 0);   
    Blynk.virtualWrite(AUTO_PIN, 0);     
}

BLYNK_CONNECTED()
{
    updateBlynkData();

    resetBlynkWidgetsToDefault();
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