/*  
    * File:   main.c
    * Author: kfree
    * Created on 2026-03-22
    * Description: Main file for the SY-3_STMX project. This file initializes the system and contains the main loop.
    * Note: Test blinking an led (for testing the board and the development environment). The led is connected to PA0 pin of the STM32F103RCT6 board. The system clock is configured to use the PLL with HSE as source, resulting in a system clock of 72 MHz.
    * Hardware: STM32F103RCT6, Led connected to PA0, 220 ohm resistor in series, and GND.
    * Power supply: board powered by USB and led connected to 3.3V pin of the board.
*/

#include "stm32f1xx_hal.h"

static void SystemClock_Config(void);
static void GPIO_LED_Init(void);

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  GPIO_LED_Init();

  // OFF au départ (active‑LOW => niveau HAUT = OFF)
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);

  while (1) {
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_5);
    HAL_Delay(300);
  }
}

static void GPIO_LED_Init(void)
{
  __HAL_RCC_GPIOC_CLK_ENABLE();              // <— IMPORTANT pour PCx

  GPIO_InitTypeDef io = {0};
  io.Pin   = GPIO_PIN_5;                     // PC5
  io.Mode  = GPIO_MODE_OUTPUT_PP;            // sortie push‑pull
  io.Pull  = GPIO_NOPULL;
  io.Speed = GPIO_SPEED_FREQ_LOW;            // F1: _LOW/_MEDIUM/_HIGH
  HAL_GPIO_Init(GPIOC, &io);
}

static void SystemClock_Config(void)
{
  RCC_OscInitTypeDef osc = {0};
  RCC_ClkInitTypeDef clk = {0};

  // HSE 8 MHz -> PLL x9 = 72 MHz
  osc.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  osc.HSEState       = RCC_HSE_ON;
  osc.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  osc.HSIState       = RCC_HSI_ON;
  osc.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  osc.PLL.PLLState   = RCC_PLL_ON;
  osc.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
  osc.PLL.PLLMUL     = RCC_PLL_MUL9;
  HAL_RCC_OscConfig(&osc);

  clk.ClockType      = RCC_CLOCKTYPE_HCLK
                     | RCC_CLOCKTYPE_SYSCLK
                     | RCC_CLOCKTYPE_PCLK1
                     | RCC_CLOCKTYPE_PCLK2;  // <— attention : bien des pipes `|`
  clk.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
  clk.AHBCLKDivider  = RCC_SYSCLK_DIV1;
  clk.APB1CLKDivider = RCC_HCLK_DIV2;       // 36 MHz
  clk.APB2CLKDivider = RCC_HCLK_DIV1;       // 72 MHz
  HAL_RCC_ClockConfig(&clk, FLASH_LATENCY_2);
}