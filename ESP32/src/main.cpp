#define BLYNK_TEMPLATE_ID "TMPL6-Osyi-Jt"
#define BLYNK_TEMPLATE_NAME "SMARTOFFICE"
#define BLYNK_AUTH_TOKEN "eR5OwSub04AeFhk1eKIFqp5da5WESDQF"

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define LED_PIN 2

char ssid[] = "P 504";
char pass[] = "12345679";

BlynkTimer timer;

// Xử lý khi nhấn nút trên app Blynk (nút gán vào V1)
BLYNK_WRITE(V1) {
  int pinValue = param.asInt();
  digitalWrite(LED_PIN, pinValue);
  Blynk.virtualWrite(V0, pinValue);  // Phản hồi trạng thái
  Serial.print("Nút V1: ");
  Serial.println(pinValue == 1 ? "BẬT" : "TẮT");
}

void sendFakeData() {
  int value = random(100, 999);
  Blynk.virtualWrite(V3, value);  // Giả lập gửi dữ liệu cảm biến
  Serial.println("Đã gửi dữ liệu giả");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println("Kết nối WiFi...");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi đã kết nối!");
  Serial.println(WiFi.localIP());

  Blynk.config(BLYNK_AUTH_TOKEN);
  Blynk.connect();

  Blynk.virtualWrite(V2, 1);  // Bật LED ảo ban đầu
  timer.setInterval(3000L, sendFakeData);
}

void loop() {
  Blynk.run();
  timer.run();
}
