/**
 *******************************************************************************
 * @file 	main.c
 * @author 	jjo
 * @date 	Mar 29, 2024
 * @brief	Fichier principal de votre projet sur carte Nucléo STM32G431KB
 *******************************************************************************
 */

#include "config.h"
#include "stm32g4_sys.h"

#include "stm32g4_systick.h"
#include "stm32g4_gpio.h"
#include "stm32g4_uart.h"
#include "tft_ili9341/stm32g4_ili9341.h"
#include "Ui/ui.h"
#include "taskmgr.h"
#include "button/button.h"

#include <stdio.h>

#include "mon_appli.h"

#define BLINK_DELAY		100	//ms
#define WIDTH 320
#define HEIGHT 240
#define NB_MAX_APPLIS		5

volatile uint8_t system_state = 0;  // 0 = OFF, 1 = ON


void write_LED(bool b)
{
	HAL_GPIO_WritePin(LED_GREEN_GPIO, LED_GREEN_PIN, b);
}

bool char_received(uart_id_t uart_id)
{
	if( BSP_UART_data_ready(uart_id) )	/* Si un caractère est reçu sur l'UART 2*/
	{
		/* On "utilise" le caractère pour vider le buffer de réception */
		BSP_UART_get_next_byte(uart_id);
		return true;
	}
	else
		return false;
}

/*
bool button_press_event(GPIO_TypeDef *GPIOx, uint16_t PIN, uint8_t Button_ID) {
	static bool previous_state[5] = {false};
	bool current_state;
	bool ret;
	current_state = !HAL_GPIO_ReadPin(GPIOx,PIN);
	ret = current_state && !previous_state[Button_ID];
	previous_state[Button_ID] = current_state;
	return ret;
}
*/


void heartbeat(void)
{
	write_LED(true);
	HAL_Delay(50);
	write_LED(false);
	HAL_Delay(1500);

	while(!char_received(UART2_ID) )
	{
		write_LED(true);
		HAL_Delay(50);
		write_LED(false);
		HAL_Delay(1500);
	}
}

void anim(void) {
	button_init();
	if(button_press_B0()){ //button_press_event(GPIOB,GPIO_PIN_0,0)
		if(system_state == 0) {
			startanim();
			system_state = 1;
		} else {
			stopanim();
			system_state = 0;
		}
	}

	if (button_press_event(GPIOB,GPIO_PIN_6,1) && system_state == 1) { // button_press_B6
		ouvrir_editeur();
		//system_state = 2;
	}
	if (button_press_event(GPIOA,GPIO_PIN_12,2) && system_state == 1) { //
		ouvrir_explorateur();
		//system_state = 2;
	}
	if (button_press_event(GPIOA,GPIO_PIN_15,3) && system_state != 0) { //
		afficher_menu();
	}

}


/**
  * @brief  Point d'entrée de votre application
  */
int main(void)
{
	/* Cette ligne doit rester la première de votre main !
	 * Elle permet d'initialiser toutes les couches basses des drivers (Hardware Abstraction Layer),
	 * condition préalable indispensable à l'exécution des lignes suivantes.
	 */
	HAL_Init();

	/* Initialisation des périphériques utilisés dans votre programme */
	BSP_GPIO_enable();
	BSP_UART_init(UART2_ID,115200);

	/* Indique que les printf sont dirigés vers l'UART2 */
	BSP_SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

	/* Initialisation du port de la led Verte (carte Nucleo) */
	BSP_GPIO_pin_config(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH,GPIO_NO_AF);

	// Configurer GPIOA Pin 12 en entrée avec pull-up
	BSP_GPIO_pin_config(GPIOB, GPIO_PIN_0, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, GPIO_NO_AF);
	BSP_GPIO_pin_config(GPIOA, GPIO_PIN_12, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, GPIO_NO_AF);
	BSP_GPIO_pin_config(GPIOA, GPIO_PIN_15, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, GPIO_NO_AF);
	BSP_GPIO_pin_config(GPIOB, GPIO_PIN_6, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, GPIO_NO_AF);
	BSP_GPIO_pin_config(GPIOB, GPIO_PIN_7, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, GPIO_NO_AF);


	/* Hello student */
	printf("Hi <Student>, can you read me?\n");

	TASKMGR_init();

	//ici, ou par l'intervention d'un menu....
	/*
	appli_t appli_game_of_life = (appli_t){
											.init = &GAME_OF_LIFE_init,
											.process_main = &GAME_OF_LIFE_process_main,
											.process_ms = &GAME_OF_LIFE_process_ms,
											.ask_for_end = &GAME_OF_LIFE_ask_for_end
											};
	uint8_t id_game_of_life;
	id_game_of_life = TASKMGR_launch_appli(&appli_game_of_life);
	*/
	/*
	appli_t mon_appli = (appli_t) {
	    .init = &MON_APPLI_init,
	    .process_main = &MON_APPLI_process_main,
	    .process_ms = &MON_APPLI_process_ms,
	    .ask_for_end = &MON_APPLI_ask_for_end
	};

	uint8_t id_appli;
	TASKMGR_launch_appli(&mon_appli, &id_appli);
	*/


	/* Tâche de fond, boucle infinie, Infinite loop,... quelque soit son nom vous n'en sortirez jamais */

	/*
	ILI9341_Init();

	ILI9341_Fill(ILI9341_COLOR_WHITE);
	ILI9341_DrawCircle(20,20,5,ILI9341_COLOR_BLUE);
	ILI9341_DrawLine(20,20,100,20,ILI9341_COLOR_RED);
	ILI9341_DrawLine(20,20,20,100,ILI9341_COLOR_RED);
	ILI9341_Putc(110,11,'x',&Font_11x18,ILI9341_COLOR_BLUE,ILI9341_COLOR_WHITE);
	ILI9341_Putc(15,110,'y',&Font_11x18,ILI9341_COLOR_BLUE,ILI9341_COLOR_WHITE);
	ILI9341_Puts(200,200, "chaine", &Font_11x18, ILI9341_COLOR_BROWN, ILI9341_COLOR_WHITE);
	*/

	//ILI9341_Init();
	//ILI9341_Fill(ILI9341_COLOR_BLACK);

	while (1)
	{
		//heartbeat();
		anim();
		TASKMGR_process_main();

		HAL_Delay(50);

		/*
		if(char_received(UART2_ID))
		{
			write_LED(true);		// write_LED? Faites un ctrl+clic dessus pour voir...
			HAL_Delay(BLINK_DELAY);	// ... ça fonctionne aussi avec les macros, les variables. C'est votre nouveau meilleur ami
			write_LED(false);
		}*/

	}
}
