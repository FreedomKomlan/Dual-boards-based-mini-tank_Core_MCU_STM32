/*  
    * File:   main.c
    * Author: kfree
    * Created on 2026-03-22
    * Description: Main file for the SY-3_STMX project. This file initializes the system and contains the main loop.
    * Note: Test blinking an led (for testing the board and the development environment). The led is connected to PA0 pin of the STM32F103RCT6 board. The system clock is configured to use the PLL with HSE as source, resulting in a system clock of 72 MHz.
    * Hardware: STM32F103RCT6, Led connected to PA0, 220 ohm resistor in series, and GND.
    * Power supply: board powered by USB and led connected to 3.3V pin of the board.
*/

#include "stm32f1xx.h"  // CMSIS device header (fourni par STM32CubeF1)

#define LED_PORT   GPIOC
#define LED_PIN    5U               // PC5

static void delay(volatile uint32_t t)
{
    while (t--) __NOP();            // attente "busy-wait" (approx)
}

int main(void)
{
    /* 1) Activer l'horloge du port C (APB2) */
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    /* 2) Configurer PC5 en sortie push‑pull 2 MHz
          - Sur STM32F1, pins 0..7 utilisent CRL ; pins 8..15 CRH
          - Chaque pin a un "nibble" de 4 bits : [CNF1:0 | MODE1:0]
            Sortie push‑pull 2 MHz => CNF=00, MODE=10 => 0b0010 (0x2)     */
    LED_PORT->CRL &= ~(0xFU << (LED_PIN * 4));      // clear le nibble de PC5
    LED_PORT->CRL |=  (0x2U << (LED_PIN * 4));      // MODE=10, CNF=00

    /* 3) État initial OFF pour une LED active‑LOW (mettre la broche à 1) */
    LED_PORT->BSRR = (1U << LED_PIN);               // SET => OFF (active‑LOW)

    /* 4) Boucle : ON 300 ms, OFF 300 ms */
    while (1)
    {
        /* ON (active‑LOW) : mettre la broche à 0 V */
        LED_PORT->BRR  = (1U << LED_PIN);           // RESET => ON
        delay(300000);

        /* OFF : remettre la broche à 3.3 V */
        LED_PORT->BSRR = (1U << LED_PIN);           // SET   => OFF
        delay(300000);
    }
}