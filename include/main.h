/*
    * main.h
    * Author: Komlan Freedom TSOKPO
    * Created on: 2026-04-05
    * I just followed the same structure as in STM32CubeIDE
    * Instead of including stm32f1xx_hal.h in main.c, I included it in main.h and then included main.h in main.c. This way, if I need to include other header files in the future, I can just include them in main.h and they will be available in main.c without having to include them separately.
    * This is a common practice in C programming to have a main header file that includes all
*/

#ifndef MAIN_H
#define MAIN_H
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "stm32f1xx_hal.h"
#include "config.h"

void Error_Handler(void);


#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAIN_H