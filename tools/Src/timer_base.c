#include "timer_base.h"

volatile uint32_t _millis = 0;

/**
 * @brief  Khởi tạo TIM2 để tạo ngắt mỗi 1ms. Dùng cho millis() và Delay_ms().
 * 
 * @note   TIM2 sẽ đếm với tần số 1kHz (1ms mỗi lần tràn) và tạo ngắt Update (UIE).
 *         Biến _millis sẽ tăng trong hàm ngắt TIM2_IRQHandler().
 */
void Timer2_Init(void)
{
    __HAL_RCC_TIM2_CLK_ENABLE();

    TIM_HandleTypeDef htim2;
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = (SystemCoreClock / 1000) - 1;  // Tạo tick 1ms
    htim2.Init.Period = 1 - 1;                            // Tràn mỗi 1ms
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

    TIM_Base_Init(&htim2);

    TIM2->DIER |= TIM_DIER_UIE;      // Cho phép ngắt update
    NVIC_EnableIRQ(TIM2_IRQn);       // Bật TIM2 interrupt trong NVIC

    TIM2->CR1 |= TIM_CR1_CEN;        // Bắt đầu đếm
}

/**
 * @brief  Hàm ngắt TIM2: tăng biến đếm millis mỗi 1ms
 */
void TIM2_IRQHandler(void)
{
    if (TIM2->SR & TIM_SR_UIF)
    {
        TIM2->SR &= ~TIM_SR_UIF;  // Xóa cờ ngắt update
        _millis++;                // Tăng biến millis
    }
}

/**
 * @brief  Trả về số millisecond kể từ khi khởi động Timer2.
 * 
 * @return uint32_t : thời gian tính bằng mili giây
 */
uint32_t millis(void)
{
    return _millis;
}

/**
 * @brief  Delay chính xác theo micro giây bằng DWT Cycle Counter
 * 
 * @note   Trước khi sử dụng hàm này, cần bật DWT bằng cách thêm vào trong hàm main():
 *           CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
 *           DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
 * 
 *         Nếu không bật DWT, hàm sẽ không hoạt động đúng hoặc bị treo.
 * 
 * @param  us: thời gian delay (micro giây)
 */
void Delay_us(uint16_t us)
{
    uint32_t start = DWT->CYCCNT;
    uint32_t ticks = us * (SystemCoreClock / 1000000);
    while ((DWT->CYCCNT - start) < ticks);
}

/**
 * @brief  Delay theo mili giây (dựa trên biến _millis tăng mỗi 1ms từ TIM2)
 * 
 * @param  ms: thời gian delay (mili giây)
 */
void Delay_ms(uint32_t ms)
{
    uint32_t start = millis();
    while ((millis() - start) < ms);
}
