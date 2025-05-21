#ifndef BUTTON_BUTTON_H_
#define BUTTON_BUTTON_H_

#include "config.h"
#include "stm32g4_sys.h"

bool button_press_A15(void);
bool button_press_A12(void);
bool button_press_B0(void);
bool button_press_B6(void);
bool button_press_B7(void);
bool button_press_event(GPIO_TypeDef *GPIOx, uint16_t PIN, uint8_t Button_ID);

#endif
