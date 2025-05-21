#ifndef TASKMGR_H
#define TASKMGR_H

#include <stdbool.h>
#include <stdint.h>
#include "stm32g4_sys.h"
#include "stm32g4_systick.h"
#include "stm32g4_gpio.h"
#include "stm32g4_uart.h"
#include "config.h"
#include "stm32g4_utils.h"


typedef running_t(*process_main_fun_t)(void);	//Type pointeur sur fonction qui renvoit un running_e

typedef struct
{
	bool enable;
	process_main_fun_t process_main;
	callback_fun_t process_ms;
	callback_fun_t init;
	callback_fun_t ask_for_end;
}appli_t;


void TASKMGR_init(void);
running_t TASKMGR_launch_appli(appli_t * appli, uint8_t * id);
running_t TASKMGR_kill_appli(process_main_fun_t pfun);
running_t TASKMGR_kill_app(uint8_t id);
void TASKMGR_process_main(void);

static void TASKMGR_process_ms(void);

#endif
