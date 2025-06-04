#include "device_manager.h"

/**
 * @brief Khởi tạo tất cả biến cảm biến và thiết bị điều khiển về giá trị mặc định.
 */
device_manager::device_manager()
{
  // Khởi tạo cảm biến
  ldr_lux.data_float = 400.00f;
  gas_ppm.data_float = 150.00f;
  dht_temperature.data_float = 25.0f;
  dht_humidity.data_float = 50.0f;

  // Khởi tạo thiết bị điều khiển
  led_status.data_float = 0.0f;   // LED tắt
  motor_speed.data_float = 0.0f;  // Motor dừng
  siren_status.data_float = 0.0f; // Siren tắt
  auto_mode.data_float = 0.0f;    // Chế độ tự động tắt
}

// ===== LDR =====
void device_manager::setLdrLux(float value)
{
  ldr_lux.data_float = value;
}
void device_manager::setLdrLuxBytes(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4)
{
  float value = Convert_Bytes_To_Float(data1, data2, data3, data4);
  ldr_lux.data_float = value;
}
float device_manager::getLdrLux() const
{
  return ldr_lux.data_float;
}

// ===== Gas Sensor =====
void device_manager::setGasPPM(float value)
{
  gas_ppm.data_float = value;
}
void device_manager::setGasPPMBytes(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4)
{
  float value = Convert_Bytes_To_Float(data1, data2, data3, data4);
  gas_ppm.data_float = value;
}
float device_manager::getGasPPM() const
{
  return gas_ppm.data_float;
}

// ===== DHT Temperature =====
void device_manager::setDhtTemperature(float value)
{
  dht_temperature.data_float = value;
}
void device_manager::setDhtTemperatureBytes(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4)
{
  float value = Convert_Bytes_To_Float(data1, data2, data3, data4);
  dht_temperature.data_float = value;
}
float device_manager::getDhtTemperature() const
{
  return dht_temperature.data_float;
}

// ===== DHT Humidity =====
void device_manager::setDhtHumidity(float value)
{
  dht_humidity.data_float = value;
}
void device_manager::setDhtHumidityBytes(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4)
{
  float value = Convert_Bytes_To_Float(data1, data2, data3, data4);
  dht_humidity.data_float = value;
}
float device_manager::getDhtHumidity() const
{
  return dht_humidity.data_float;
}

// ===== LED =====
void device_manager::setLEDStatus(float value)
{
  led_status.data_float = value;
}

void device_manager::setLEDStatusBytes(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4)
{
  float value = Convert_Bytes_To_Float(data1, data2, data3, data4);
  led_status.data_float = value;
}

float device_manager::getLEDStatus() const
{
  return led_status.data_float;
}

// ===== Motor =====
void device_manager::setMotorSpeed(float value)
{
  motor_speed.data_float = value;
}

void device_manager::setMotorSpeedBytes(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4)
{
  float value = Convert_Bytes_To_Float(data1, data2, data3, data4);
  motor_speed.data_float = value;
}

float device_manager::getMotorSpeed() const
{
  return motor_speed.data_float;
}

// ===== Siren =====
void device_manager::setSirenStatus(float value)
{
  siren_status.data_float = value;
}

void device_manager::setSirenStatusBytes(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4)
{
  float value = Convert_Bytes_To_Float(data1, data2, data3, data4);
  siren_status.data_float = value;
}

float device_manager::getSirenStatus() const
{
  return siren_status.data_float;
}

// ===== Auto Mode =====
void device_manager::setAutoMode(float value)
{
  auto_mode.data_float = value;
}

void device_manager::setAutoModeBytes(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4)
{
  float value = Convert_Bytes_To_Float(data1, data2, data3, data4);
  auto_mode.data_float = value;
}

float device_manager::getAutoMode() const
{
  return auto_mode.data_float;
}