#include "BlynkHandler.h"

// char ssid[] = "Son Heung -min 2G";
// char pass[] = "";

BlynkTimer timer;

void sendFakeSensorData() {
  int sound = random(100, 600);           // Âm thanh
  int light = random(300, 1023);          // Ánh sáng
  int gas = random(200, 800);             // Nồng độ khí gas
  float temp = random(250, 350) / 10.0;   // Nhiệt độ
  int humid = random(40, 90);             // Độ ẩm
  int ir = random(0, 2);                  // IR phát hiện

  Blynk.virtualWrite(V0, sound);
  Blynk.virtualWrite(V1, light);
  Blynk.virtualWrite(V2, gas);
  Blynk.virtualWrite(V3, temp);
  Blynk.virtualWrite(V4, humid);
  Blynk.virtualWrite(V5, ir);

  Serial.println("Đã gửi dữ liệu giả lập lên Blynk");
}

// Hàm xử lý nút từ App Blynk
BLYNK_WRITE(V6) {
  int pinValue = param.asInt(); // 0 hoặc 1
  digitalWrite(LED_PIN, pinValue);
  Serial.print("Trạng thái LED: ");
  Serial.println(pinValue == 1 ? "BẬT" : "TẮT");
}

void setupBlynk() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(3000L, sendFakeSensorData);
}
