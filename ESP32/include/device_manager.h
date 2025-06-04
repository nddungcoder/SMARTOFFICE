#ifndef DEVICE_MANAGER_H_
#define DEVICE_MANAGER_H_

#include <stdint.h>
#include <string.h>
#include "convert.h"

/**
 * @brief Lớp quản lý các thiết bị sensor và actuator.
 *
 * Lưu trữ giá trị từ các cảm biến (LDR, MQ2, DHT11) và
 * trạng thái thiết bị điều khiển (LED, motor, còi báo động).
 * Cho phép truy xuất dữ liệu thông qua các hàm set/get dưới dạng float hoặc byte.
 */
class device_manager
{
private:
  // Biến cảm biến
  data_convert_float_and_bytes ldr_lux;
  data_convert_float_and_bytes gas_ppm;
  data_convert_float_and_bytes dht_temperature;
  data_convert_float_and_bytes dht_humidity;

  // Biến thiết bị điều khiển
  data_convert_float_and_bytes led_status;
  data_convert_float_and_bytes motor_speed;
  data_convert_float_and_bytes siren_status;

  // Trạng thái chế độ tự động
  data_convert_float_and_bytes auto_mode;

public:
  /**
   * @brief Constructor khởi tạo tất cả thiết bị với giá trị mặc định.
   */
  device_manager();

  // ===== LDR Sensor =====

  /**
   * @brief Thiết lập giá trị ánh sáng LDR theo float.
   * @param value Độ sáng (lux).
   */
  void setLdrLux(float value);

  /**
   * @brief Thiết lập giá trị LDR theo 4 byte.
   */
  void setLdrLuxBytes(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);

  /**
   * @brief Lấy giá trị độ sáng LDR.
   */
  float getLdrLux() const;

  // ===== Gas Sensor =====

  void setGasPPM(float value);
  void setGasPPMBytes(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);
  float getGasPPM() const;

  // ===== DHT11 Sensor =====

  void setDhtTemperature(float value);
  void setDhtTemperatureBytes(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);
  float getDhtTemperature() const;

  void setDhtHumidity(float value);
  void setDhtHumidityBytes(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);
  float getDhtHumidity() const;

  // ===== LED Actuator =====

  void setLEDStatus(float value);
  void setLEDStatusBytes(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);
  float getLEDStatus() const;

  // ===== Motor Actuator =====

  void setMotorSpeed(float value);
  void setMotorSpeedBytes(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);
  float getMotorSpeed() const;

  // ===== Siren Actuator =====

  void setSirenStatus(float value);
  void setSirenStatusBytes(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);
  float getSirenStatus() const;

  // ===== Auto Mode =====

  void setAutoMode(float value);
  void setAutoModeBytes(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);
  float getAutoMode() const;
};

#endif // DEVICE_MANAGER_H_
