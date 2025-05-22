#ifndef INC_STM32F103xx_H_
#define INC_STM32F103xx_H_

#include "stdint.h"

#define FLASH_BASEADDR 0x08000000U
#define SRAM_BASEADDR 0x20000000U
#define PERIPH_BASEADDR 0x40000000U

/* Peripheral Base Addresses (AHB, APB1, APB2 buses) */
#define APB1PERIPH_BASE     PERIPH_BASEADDR
#define APB2PERIPH_BASE     (PERIPH_BASEADDR + 0x00010000U)
#define AHBPERIPH_BASE      (PERIPH_BASEADDR + 0x00020000U)

/* APB2 Peripherals */
#define GPIOA_BASEADDR      (APB2PERIPH_BASE + 0x0800U)
#define GPIOB_BASEADDR      (APB2PERIPH_BASE + 0x0C00U)
#define GPIOC_BASEADDR      (APB2PERIPH_BASE + 0x1000U)
#define GPIOD_BASEADDR      (APB2PERIPH_BASE + 0x1400U)
#define GPIOE_BASEADDR      (APB2PERIPH_BASE + 0x1800U)
#define AFIO_BASEADDR       (APB2PERIPH_BASE + 0x0000U)
#define EXTI_BASEADDR       (APB2PERIPH_BASE + 0x0400U)
#define USART1_BASEADDR     (APB2PERIPH_BASE + 0x3800U)
#define SPI1_BASEADDR       (APB2PERIPH_BASE + 0x3000U)
#define TIM1_BASEADDR       (APB2PERIPH_BASE + 0x2C00U)

/* APB1 Peripherals */
#define TIM2_BASEADDR       (APB1PERIPH_BASE + 0x0000U)
#define TIM3_BASEADDR       (APB1PERIPH_BASE + 0x0400U)
#define TIM4_BASEADDR       (APB1PERIPH_BASE + 0x0800U)
#define USART2_BASEADDR     (APB1PERIPH_BASE + 0x4400U)
#define USART3_BASEADDR     (APB1PERIPH_BASE + 0x4800U)
#define SPI2_BASEADDR       (APB1PERIPH_BASE + 0x3800U)
#define I2C1_BASEADDR       (APB1PERIPH_BASE + 0x5400U)

/* AHB Peripherals */
#define DMA1_BASEADDR       (AHBPERIPH_BASE + 0x0000U)
#define RCC_BASEADDR        (AHBPERIPH_BASE + 0x1000U)
#define FLASH_R_BASEADDR    ((uint32_t)0x40022000U)

/* -------- GPIO Register Definition -------- */
typedef struct
{
  volatile uint32_t CRL;    // Port configuration register low (GPIOx_CRL)
  volatile uint32_t CRH;    // Port configuration register high (GPIOx_CRH)
  volatile uint32_t IDR;    // Port input data register (GPIOx_IDR)
  volatile uint32_t ODR;    // Port output data register (GPIOx_ODR)
  volatile uint32_t BSRR;   // Port bit set/reset register (GPIOx_BSRR)
  volatile uint32_t BRR;    // Port bit reset register (GPIOx_BRR)
  volatile uint32_t LCKR;   // Port configuration lock register (GPIOx_LCKR)
} GPIO_RegDef_t;

/* -------- AFIO Register Definition -------- */
typedef struct
{
    volatile uint32_t EVCR;      // 0x00
    volatile uint32_t MAPR;      // 0x04
    volatile uint32_t EXTICR[4]; // 0x08 - 0x14 (EXTICR1,2,3,4)
    volatile uint32_t MAPR2;     // 0x18
} AFIO_RegDef_t;

/* --- EXTI Register Definition --- */
typedef struct
{
  volatile uint32_t IMR;
  volatile uint32_t EMR;
  volatile uint32_t RTSR;
  volatile uint32_t FTSR;
  volatile uint32_t SWIER;
  volatile uint32_t PR;
} EXTI_RegDef_t;

/* -------- RCC Register Definition -------- */
typedef struct
{
  volatile uint32_t CR;         // Clock control register (RCC_CR)
  volatile uint32_t CFGR;       // Clock configuration register (RCC_CFGR)
  volatile uint32_t CIR;        // Clock interrupt register (RCC_CIR)
  volatile uint32_t APB2RSTR;   // APB2 peripheral reset register (RCC_APB2RSTR)
  volatile uint32_t APB1RSTR;   // APB1 peripheral reset register (RCC_APB1RSTR)
  volatile uint32_t AHBENR;     // AHB peripheral clock enable register (RCC_AHBENR)
  volatile uint32_t APB2ENR;    // APB2 peripheral clock enable register (RCC_APB2ENR)
  volatile uint32_t APB1ENR;    // APB1 peripheral clock enable register (RCC_APB1ENR)
  volatile uint32_t BDCR;       // Backup domain control register (RCC_BDCR)
  volatile uint32_t CSR;        // Control/status register (RCC_CSR)
} RCC_RegDef_t;

/* -------- USART Register Definition -------- */
typedef struct
{
  volatile uint32_t SR;     // Status register (USART_SR)
  volatile uint32_t DR;     // Data register (USART_DR)
  volatile uint32_t BRR;    // Baud rate register (USART_BRR)
  volatile uint32_t CR1;    // Control register 1 (USART_CR1)
  volatile uint32_t CR2;    // Control register 2 (USART_CR2)
  volatile uint32_t CR3;    // Control register 3 (USART_CR3)
  volatile uint32_t GTPR;   // Guard time and prescaler register (USART_GTPR)
} USART_RegDef_t;

/* -------- SPI Register Definition -------- */
typedef struct
{
  volatile uint32_t CR1;    // Control register 1 (SPI_CR1)
  volatile uint32_t CR2;    // Control register 2 (SPI_CR2)
  volatile uint32_t SR;     // Status register (SPI_SR)
  volatile uint32_t DR;     // Data register (SPI_DR)
  volatile uint32_t CRCPR;  // CRC polynomial register (SPI_CRCPR)
  volatile uint32_t RXCRCR; // RX CRC register (SPI_RXCRCR)
  volatile uint32_t TXCRCR; // TX CRC register (SPI_TXCRCR)
} SPI_RegDef_t;

/* -------- I2C Register Definition -------- */
typedef struct
{
  volatile uint32_t CR1;    // Control register 1 (I2C_CR1)
  volatile uint32_t CR2;    // Control register 2 (I2C_CR2)
  volatile uint32_t OAR1;   // Own address register 1 (I2C_OAR1)
  volatile uint32_t OAR2;   // Own address register 2 (I2C_OAR2)
  volatile uint32_t DR;     // Data register (I2C_DR)
  volatile uint32_t SR1;    // Status register 1 (I2C_SR1)
  volatile uint32_t SR2;    // Status register 2 (I2C_SR2)
  volatile uint32_t CCR;    // Clock control register (I2C_CCR)
  volatile uint32_t TRISE;  // TRISE register
} I2C_RegDef_t;

/* -------- Define peripherals with addresses base -------- */
#define GPIOA   ((GPIO_RegDef_t*) GPIOA_BASEADDR)
#define GPIOB   ((GPIO_RegDef_t*) GPIOB_BASEADDR)
#define GPIOC   ((GPIO_RegDef_t*) GPIOC_BASEADDR)
#define GPIOD   ((GPIO_RegDef_t*) GPIOD_BASEADDR)
#define GPIOE   ((GPIO_RegDef_t*) GPIOE_BASEADDR)

#define AFIO   ((AFIO_RegDef_t*) AFIO_BASEADDR)

#define RCC     ((RCC_RegDef_t*) RCC_BASEADDR)
#define EXTI    ((EXTI_RegDef_t*) EXTI_BASEADDR)

#define USART1  ((USART_RegDef_t*) USART1_BASEADDR)
#define USART2  ((USART_RegDef_t*) USART2_BASEADDR)
#define USART3  ((USART_RegDef_t*) USART3_BASEADDR)

#define SPI1    ((SPI_RegDef_t*) SPI1_BASEADDR)
#define SPI2    ((SPI_RegDef_t*) SPI2_BASEADDR)

#define I2C1    ((I2C_RegDef_t*) I2C1_BASEADDR)

/*
 * Clock Enble Macros for AFIO peripherals
 */
#define AFIO_PCLK_EN() (RCC->APB2ENR |= (1 << 0))

/* Clock Enable Macros for APB2 peripherals */
#define GPIOA_PCLK_EN()     (RCC->APB2ENR |= (1 << 2))
#define GPIOB_PCLK_EN()     (RCC->APB2ENR |= (1 << 3))
#define GPIOC_PCLK_EN()     (RCC->APB2ENR |= (1 << 4))
#define GPIOD_PCLK_EN()     (RCC->APB2ENR |= (1 << 5))
#define GPIOE_PCLK_EN()     (RCC->APB2ENR |= (1 << 6))
#define ADC1_PCLK_EN()      (RCC->APB2ENR |= (1 << 9))
#define ADC2_PCLK_EN()      (RCC->APB2ENR |= (1 << 10))
#define TIM1_PCLK_EN()      (RCC->APB2ENR |= (1 << 11))
#define SPI1_PCLK_EN()      (RCC->APB2ENR |= (1 << 12))
#define USART1_PCLK_EN()    (RCC->APB2ENR |= (1 << 14))

/* Clock Disable Macros for APB2 peripherals */
#define AFIO_PCLK_DI()      (RCC->APB2ENR &= ~(1 << 0))
#define GPIOA_PCLK_DI()     (RCC->APB2ENR &= ~(1 << 2))
#define GPIOB_PCLK_DI()     (RCC->APB2ENR &= ~(1 << 3))
#define GPIOC_PCLK_DI()     (RCC->APB2ENR &= ~(1 << 4))
#define GPIOD_PCLK_DI()     (RCC->APB2ENR &= ~(1 << 5))
#define GPIOE_PCLK_DI()     (RCC->APB2ENR &= ~(1 << 6))
#define ADC1_PCLK_DI()      (RCC->APB2ENR &= ~(1 << 9))
#define ADC2_PCLK_DI()      (RCC->APB2ENR &= ~(1 << 10))
#define TIM1_PCLK_DI()      (RCC->APB2ENR &= ~(1 << 11))
#define SPI1_PCLK_DI()      (RCC->APB2ENR &= ~(1 << 12))
#define USART1_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 14))

/* Clock Enable Macros for APB1 peripherals */
#define TIM2_PCLK_EN()      (RCC->APB1ENR |= (1 << 0))
#define TIM3_PCLK_EN()      (RCC->APB1ENR |= (1 << 1))
#define TIM4_PCLK_EN()      (RCC->APB1ENR |= (1 << 2))
#define SPI2_PCLK_EN()      (RCC->APB1ENR |= (1 << 14))
#define USART2_PCLK_EN()    (RCC->APB1ENR |= (1 << 17))
#define USART3_PCLK_EN()    (RCC->APB1ENR |= (1 << 18))
#define I2C1_PCLK_EN()      (RCC->APB1ENR |= (1 << 21))

/* Clock Disable Macros for APB1 peripherals */
#define TIM2_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 0))
#define TIM3_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 1))
#define TIM4_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 2))
#define SPI2_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 14))
#define USART2_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 17))
#define USART3_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 18))
#define I2C1_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 21))

/* Clock Enable Macros for AHB peripherals */
#define DMA1_PCLK_EN()      (RCC->AHBENR |= (1 << 0))
#define SRAM_PCLK_EN()      (RCC->AHBENR |= (1 << 2))
#define FLITF_PCLK_EN()     (RCC->AHBENR |= (1 << 4))
#define CRC_PCLK_EN()       (RCC->AHBENR |= (1 << 6))
#define FSMC_PCLK_EN()      (RCC->AHBENR |= (1 << 8))

/* Clock Disable Macros for AHB peripherals */
#define DMA1_PCLK_DI()      (RCC->AHBENR &= ~(1 << 0))
#define SRAM_PCLK_DI()      (RCC->AHBENR &= ~(1 << 2))
#define FLITF_PCLK_DI()     (RCC->AHBENR &= ~(1 << 4))
#define CRC_PCLK_DI()       (RCC->AHBENR &= ~(1 << 6))
#define FSMC_PCLK_DI()      (RCC->AHBENR &= ~(1 << 8))

#define ENABLE 1
#define DISABLE 0
#define SET ENABLE
#define RESET DISABLE
#define GPIO_PIN_SET SET
#define GPIO_PIN_RESET RESET
#define FLAG_SET SET
#define FLAG_RESET RESET




#endif
