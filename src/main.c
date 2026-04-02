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

#define LED_PIN GPIO_PIN_5
#define LED_GPIO_PORT GPIOC
#define LED_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()

void LED_Init(void);

int main(void) {
    HAL_Init(); // Initialize the HAL Library
    LED_Init(); // Initialize the LED GPIO

    while (1) {
        HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN); // Toggle the LED
        HAL_Delay(500); // Delay for 500 ms
    }
}

void LED_Init(void) {
    LED_GPIO_CLK_ENABLE(); // Enable the clock for GPIOC
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = LED_PIN; // Configure the pin for the LED
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Set the pin as push-pull output
    GPIO_InitStruct.Pull = GPIO_NOPULL; // No pull-up or pull-down resistors
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // Set the speed to low
    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct); // Initialize the GPIO with the specified settings
}

