#ifndef APP_MAIN_H
#define APP_MAIN_H

/**
 * @brief Chế độ vận hành của hệ thống.
 *
 * AUTO_MODE: Vận hành tự động dựa trên cảm biến và logic xử lý.
 * MANUAL_MODE: Vận hành thủ công theo điều khiển từ người dùng.
 */
typedef enum {
    AUTO_MODE = 0,   ///< Chế độ tự động
    MANUAL_MODE = 1  ///< Chế độ thủ công
} MODE;

/**
 * @brief Cấu trúc lưu trữ trạng thái hệ thống.
 *
 * Bao gồm các giá trị đo từ cảm biến (nhiệt độ, độ ẩm, khí gas, ánh sáng)
 * và trạng thái của các thiết bị điều khiển như đèn, động cơ, còi.
 */
typedef struct {
    float temperature;     ///< Nhiệt độ từ cảm biến DHT11
    float humidity;        ///< Độ ẩm từ cảm biến DHT11
    float gas_level;       ///< Mức khí gas từ MQ2
    float lux;             ///< Mức ánh sáng từ LDR

    float led_r, led_g, led_b; ///< Giá trị màu RGB của LED
    float led_state;           ///< Trạng thái bật/tắt LED (1: bật, 0: tắt)

    float motor_level;     ///< Mức độ hoạt động của motor (0–100%)
    float motor_dir;       ///< Hướng quay motor (1: thuận, -1: nghịch)

    float siren_on;        ///< Trạng thái còi báo động (1: bật, 0: tắt)

    MODE mode;             ///< Chế độ hoạt động hiện tại (AUTO hoặc MANUAL)
} SystemState;

/**
 * @brief Khởi tạo các thành phần trong ứng dụng.
 *
 * Gồm cảm biến, thiết bị điều khiển, giao tiếp và trạng thái ban đầu.
 */
void App_Init(void);

/**
 * @brief Hàm vòng lặp chính xử lý logic của ứng dụng.
 *
 * Thực thi logic điều khiển tùy thuộc vào chế độ (AUTO hoặc MANUAL),
 * xử lý dữ liệu cảm biến, gửi phản hồi và cập nhật thiết bị điều khiển.
 */
void App_Loop(void);

#endif // APP_MAIN_H
