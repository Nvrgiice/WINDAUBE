/*
 * button.c
 *
 *  Created on: Apr 30, 2025
 *      Author: Hippo
 */

#include "config.h"
#include "stm32g4_sys.h"
#include "stm32g4_gpio.h"
#include <stdio.h>
#include "tft_ili9341/stm32g4_ili9341.h"
#include "../button/button.h"
#include "tft_ili9341/stm32g4_xpt2046.h"
#include "stm32g4_gpio.h"

void button_init(void) {
	BSP_GPIO_pin_config(GPIOB, GPIO_PIN_0, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, GPIO_NO_AF);
	BSP_GPIO_pin_config(GPIOA, GPIO_PIN_12, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, GPIO_NO_AF);
	BSP_GPIO_pin_config(GPIOA, GPIO_PIN_15, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, GPIO_NO_AF);
	BSP_GPIO_pin_config(GPIOB, GPIO_PIN_6, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, GPIO_NO_AF);
	BSP_GPIO_pin_config(GPIOB, GPIO_PIN_7, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, GPIO_NO_AF);
}

bool button_press_A15(void) {
	BSP_GPIO_pin_config(GPIOA, GPIO_PIN_12, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, GPIO_NO_AF);
	static bool previous_state = false;
	bool current_state;
	bool ret;
	current_state = !HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_15);
	ret = current_state && !previous_state;
	previous_state = current_state;
	return ret;
}

bool button_press_A12(void) {
	BSP_GPIO_pin_config(GPIOA, GPIO_PIN_15, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, GPIO_NO_AF);
	static bool previous_state = false;
	bool current_state;
	bool ret;
	current_state = !HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12);
	ret = current_state && !previous_state;
	previous_state = current_state;
	return ret;
}

bool button_press_B0(void) {
	BSP_GPIO_pin_config(GPIOB, GPIO_PIN_0, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, GPIO_NO_AF);
	static bool previous_state = false;
	bool current_state;
	bool ret;
	current_state = !HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0);
	ret = current_state && !previous_state;
	previous_state = current_state;
	return ret;
}

bool button_press_B6(void) {
	BSP_GPIO_pin_config(GPIOB, GPIO_PIN_6, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, GPIO_NO_AF);
	static bool previous_state = false;
	bool current_state;
	bool ret;
	current_state = !HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6);
	ret = current_state && !previous_state;
	previous_state = current_state;
	return ret;
}

bool button_press_B7(void) {
	BSP_GPIO_pin_config(GPIOB, GPIO_PIN_7, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, GPIO_NO_AF);
	static bool previous_state = false;
	bool current_state;
	bool ret;
	current_state = !HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7);
	ret = current_state && !previous_state;
	previous_state = current_state;
	return ret;
}

bool button_press_event(GPIO_TypeDef *GPIOx, uint16_t PIN, uint8_t Button_ID) {
	static bool previous_state[5] = {false};
	bool current_state;
	bool ret;
	current_state = !HAL_GPIO_ReadPin(GPIOx,PIN);
	ret = current_state && !previous_state[Button_ID];
	previous_state[Button_ID] = current_state;
	return ret;
}
