/*
 * convert.h
 *
 *  Created on: May 22, 2025
 *      Author: nguye
 */

#ifndef CONVERT_H_
#define CONVERT_H_

#include <stdint.h>
#include <Arduino.h>

/**
 * @brief Union hỗ trợ chuyển đổi giữa int và mảng 4 byte.
 */
typedef union 
{
  int data_int;
  uint8_t data_bytes[4];
} data_convert_int_and_bytes;

/**
 * @brief Union hỗ trợ chuyển đổi giữa float và mảng 4 byte.
 */
typedef union
{
  float data_float;
  uint8_t data_bytes[4];
} data_convert_float_and_bytes;

/**
 * @brief Union hỗ trợ chuyển đổi giữa uint16_t và mảng 2 byte.
 */
typedef union
{
  uint16_t data_uint16;
  uint8_t data_bytes[2];
} data_convert_uint16_and_bytes;

/**
 * @brief Chuyển đổi số nguyên int sang mảng 4 byte.
 * @param data Số nguyên cần chuyển.
 * @return Con trỏ tới mảng 4 byte đại diện cho dữ liệu int.
 */
uint8_t *Convert_Int_To_Bytes(int data);

/**
 * @brief Chuyển đổi số thực float sang mảng 4 byte.
 * @param data Số thực cần chuyển.
 * @return Con trỏ tới mảng 4 byte đại diện cho dữ liệu float.
 */
uint8_t *Convert_Float_To_Bytes(float data);

/**
 * @brief Chuyển đổi uint16_t sang mảng 2 byte.
 * @param data Số nguyên không dấu 16-bit cần chuyển.
 * @return Con trỏ tới mảng 2 byte.
 */
uint8_t *Convert_Uint16_To_Bytes(uint16_t data);

/**
 * @brief Chuyển 4 byte về kiểu int.
 * @param data1 Byte cao nhất.
 * @param data2 Byte tiếp theo.
 * @param data3 Byte tiếp theo.
 * @param data4 Byte thấp nhất.
 * @return Số nguyên int được ghép từ 4 byte.
 */
int Convert_Bytes_To_Int(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);

/**
 * @brief Chuyển 4 byte về kiểu float.
 * @param data1 Byte cao nhất.
 * @param data2 Byte tiếp theo.
 * @param data3 Byte tiếp theo.
 * @param data4 Byte thấp nhất.
 * @return Số thực float được ghép từ 4 byte.
 */
float Convert_Bytes_To_Float(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);

/**
 * @brief Chuyển 2 byte về kiểu uint16_t.
 * @param data1 Byte cao.
 * @param data2 Byte thấp.
 * @return Giá trị uint16_t ghép từ 2 byte.
 */
uint16_t Convert_Bytes_To_Uint16(uint8_t data1, uint8_t data2);

#endif /* CONVERT_H_ */
