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

void SystemClock_Config(void);
void Led_Init(void);
// void MX_GPIO_Init(void);

int main(void)
{
    HAL_Init();
    // SystemClock_Config(); // Configure the system clock if needed
    SystemClock_Config(); // Configure the system clock if needed
    Led_Init(); // Initialize the LED

    while (1)
    {
        // Main loop
        // HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0); // Toggle the LED state
        // HAL_Delay(500); // Wait for 500 milliseconds
    }
}

// Functions needed

void SystemClock_Config(void)
{
    // Configure the system clock here if necessary
    RCC_OscInitTypeDef RCC_OscInitStruct = {0}; // Structure to hold oscillator configuration parameters
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0}; // Structure to hold clock configuration parameters
    // Configure the main internal regulator output voltage
    // __HAL_RCC_PWR_CLK_ENABLE(); // Enable power control clock
    // __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1); // Set voltage scaling to 1 for maximum performance

    // Initializes the RCC Oscillators according to the specified parameters
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE; // Use High-Speed External oscillator
    RCC_OscInitStruct.HSEState = RCC_HSE_ON; // Turn on the HSE
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1; // No predivision
    RCC_OscInitStruct.HSIState = RCC_HSI_ON; // Turn on the HSI as well
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT; // Use default calibration for HSI
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON; // Turn on the PLL
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE; // Use HSE as PLL source
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9; // Multiply HSE (8 MHz) by 9 to get 72 MHz system clock
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        // Initialization Error
        while(1);
    }
    // Initializes the CPU, AHB and APB buses clocks
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2; // Configure HCLK, SYSCLK, PCLK1 and PCLK2
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; // Use PLL output as system clock
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1; // HCLK = SYSCLK
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2; // PCLK1 = HCLK/2 (max 36 MHz for APB1)
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1; // PCLK2 = HCLK (max 72 MHz for APB2)
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        // Initialization Error
        while(1);
    }
}

void Led_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0}; // Structure to hold GPIO configuration parameters
    // Initialize GPIO pins here if necessary
    __HAL_RCC_GPIOA_CLK_ENABLE(); // Enable clock for GPIOA
    
    // Configure PA0 as output for the LED
    GPIO_InitStruct.Pin = GPIO_PIN_0; // Configure PA0
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Set as push-pull output
    GPIO_InitStruct.Pull = GPIO_NOPULL; // No pull-up or pull-down
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH; // Set high speed for the pin
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); // Initialize GPIOA with the configuration
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET); // Start with LED off
}