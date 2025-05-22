/*
 * stm32_gpio.c
 *
 *  Created on: May 15, 2025
 *      Author: nguye
 */

#include "stm32_gpio.h"

/* Cấp hoặc tắt clock cho cổng GPIO */
void GPIO_PeriClockControl(GPIO_RegDef_t * pGPIOx, uint8_t EnOrDi) {
    if (EnOrDi) {
        if (pGPIOx == GPIOA) {
            RCC->APB2ENR |= (1 << 2);
        } else if (pGPIOx == GPIOB) {
            RCC->APB2ENR |= (1 << 3);
        } else if (pGPIOx == GPIOC) {
            RCC->APB2ENR |= (1 << 4);
        } else if (pGPIOx == GPIOD) {
            RCC->APB2ENR |= (1 << 5);
        } else if (pGPIOx == GPIOE) {
            RCC->APB2ENR |= (1 << 6);
        }
    } else {
        if (pGPIOx == GPIOA) {
            RCC->APB2ENR &= ~(1 << 2);
        } else if (pGPIOx == GPIOB) {
            RCC->APB2ENR &= ~(1 << 3);
        } else if (pGPIOx == GPIOC) {
            RCC->APB2ENR &= ~(1 << 4);
        } else if (pGPIOx == GPIOD) {
            RCC->APB2ENR &= ~(1 << 5);
        } else if (pGPIOx == GPIOE) {
            RCC->APB2ENR &= ~(1 << 6);
        }
    }
}

/* Khởi tạo GPIO theo cấu hình trong GPIO_Handle_t */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle) {
    uint32_t temp = 0;
    uint8_t pin = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;
    uint8_t mode = pGPIOHandle->GPIO_PinConfig.GPIO_PinMode;
    uint8_t speed = pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed;
    uint8_t pupd = pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControll;
    uint8_t optype = pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType;
    uint8_t altfun = pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode;

    GPIO_RegDef_t *GPIOx = pGPIOHandle->pGPIOx;

    // 1. Bật clock cho GPIO Port
    GPIO_PeriClockControl(GPIOx, 1);

    // 2. Xác định thanh ghi CRL hay CRH
    volatile uint32_t *config_reg = (pin < 8) ? &GPIOx->CRL : &GPIOx->CRH;
    uint8_t pos = (pin % 8) * 4;

    // 3. Xóa cấu hình cũ (4 bit)
    *config_reg &= ~(0xF << pos);

    // 4. Xây dựng giá trị cấu hình mới theo STM32F1 Reference Manual

    if (mode == GPIO_MODE_INPUT_ANALOG) {
        temp = 0x0; // MODE=00 CNF=00
    } else if (mode == GPIO_MODE_INPUT_FLOATING) {
        temp = 0x4; // MODE=00 CNF=01
    } else if (mode == GPIO_MODE_INPUT_PULL) {
        temp = 0x8; // MODE=00 CNF=10
        // Kích hoạt pull-up hoặc pull-down qua ODR
        if (pupd == 1) {
            GPIOx->ODR |= (1 << pin); // Pull-up
        } else if (pupd == 2) {
            GPIOx->ODR &= ~(1 << pin); // Pull-down
        }
    } else {
        // Output mode (push-pull hoặc open-drain)
        // MODE = tốc độ (01=10MHz,10=2MHz,11=50MHz)
        // CNF = 00 PP, 01 OD, 10 AF_PP, 11 AF_OD
        uint8_t mode_bits = 0;
        if (mode == GPIO_MODE_OUTPUT_PP) mode_bits = 0x0;
        else if (mode == GPIO_MODE_OUTPUT_OD) mode_bits = 0x1;
        else if (mode == GPIO_MODE_AF_PP) mode_bits = 0x2;
        else if (mode == GPIO_MODE_AF_OD) mode_bits = 0x3;

        temp = (speed & 0x3) | (mode_bits << 2);
    }

    *config_reg |= (temp << pos);
}

/* Reset GPIO Port về trạng thái mặc định */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx) {
    if (pGPIOx == GPIOA) {
        RCC->APB2RSTR |= (1 << 2);
        RCC->APB2RSTR &= ~(1 << 2);
    } else if (pGPIOx == GPIOB) {
        RCC->APB2RSTR |= (1 << 3);
        RCC->APB2RSTR &= ~(1 << 3);
    } else if (pGPIOx == GPIOC) {
        RCC->APB2RSTR |= (1 << 4);
        RCC->APB2RSTR &= ~(1 << 4);
    } else if (pGPIOx == GPIOD) {
        RCC->APB2RSTR |= (1 << 5);
        RCC->APB2RSTR &= ~(1 << 5);
    } else if (pGPIOx == GPIOE) {
        RCC->APB2RSTR |= (1 << 6);
        RCC->APB2RSTR &= ~(1 << 6);
    }
}

/* Đọc trạng thái mức logic của 1 chân GPIO */
uint8_t GPIO_ReadFromPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber) {
    uint8_t value;
    value = (uint8_t)(pGPIOx->IDR >> PinNumber)&0x00000001;
    return value;
}

/* Đọc toàn bộ 16 bit port */
uint16_t GPIO_ReadFromPort(GPIO_RegDef_t *pGPIOx) {
    return (uint16_t)(pGPIOx->IDR);
}

/* Ghi mức logic (0 hoặc 1) ra 1 chân GPIO */
void GPIO_WriteToPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value) {
    if (Value) {
        pGPIOx->BSRR = (1 << PinNumber); // Set bit
    } else {
        pGPIOx->BRR = (1 << PinNumber);  // Reset bit
    }
}

/* Ghi toàn bộ 16 bit port */
void GPIO_WriteToPort(GPIO_RegDef_t *pGPIOx, uint16_t Value) {
    pGPIOx->ODR = Value;
}

/* Đảo trạng thái chân GPIO */
void GPIO_TogglePin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber) {
    pGPIOx->ODR ^= (1 << PinNumber);
}

/* Cấu hình IRQ cho GPIO */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnOrDi) {
    if (EnOrDi) {
        if (IRQNumber <= 31) {
            *(volatile uint32_t *)(0xE000E100 + (IRQNumber / 32) * 4) |= (1 << (IRQNumber % 32));
        }
    } else {
        if (IRQNumber <= 31) {
            *(volatile uint32_t *)(0xE000E100 + (IRQNumber / 32) * 4) &= ~(1 << (IRQNumber % 32));
        }
    }
}

/* Cấu hình mức ưu tiên IRQ */
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority) {
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_section = IRQNumber % 4;

    uint8_t shift_amount = (8 * iprx_section) + (8 - 4); // 4 bits priority

    *(NVIC_PR_BASE_ADDR + iprx) &= ~(0xF << shift_amount);
    *(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriority << shift_amount);
}

/* Xử lý ngắt cho GPIO */
void GPIO_IRQHandling(uint8_t PinNumber) {
    if (EXTI->PR & (1 << PinNumber)) {
        // Xóa cờ ngắt
        EXTI->PR |= (1 << PinNumber);

        // Gọi callback xử lý nếu có (user định nghĩa)
        // Ví dụ: GPIO_IRQ_Callback(PinNumber);
    }
}
