/*
 * siren.h
 *
 *  Created on: May 22, 2025
 *      Author: nguye
 */

#ifndef __SIREN_H__
#define __SIREN_H__

#include <stdint.h>

/**
 * @brief Khởi tạo siren (buzzer).
 * 
 * Cấu hình chân GPIO làm output điều khiển còi. 
 * Cần gọi hàm này trước khi sử dụng các hàm khác trong module.
 */
void Siren_Init(void);

/**
 * @brief Bật còi (mức logic HIGH).
 */
void Siren_On(void);

/**
 * @brief Tắt còi (mức logic LOW).
 */
void Siren_Off(void);

/**
 * @brief Đảo trạng thái còi (nếu đang bật thì tắt, nếu đang tắt thì bật).
 */
void Siren_Toggle(void);

/**
 * @brief Bật còi trong khoảng thời gian xác định (blocking).
 * 
 * @param duration_ms Thời gian phát còi, tính bằng mili giây.
 */
void Siren_Beep(uint32_t duration_ms);

#endif /* __SIREN_H__ */
