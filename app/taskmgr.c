#include <stdio.h>
#include "config.h"
#include "taskmgr.h"
#include "stm32g4_sys.h"
#include "tft_ili9341/stm32g4_ili9341.h"

#define NB_MAX_APPLIS		5

#define WIDTH 320
#define HEIGHT 240

appli_t applis[NB_MAX_APPLIS];

void TASKMGR_init(void)
{
	BSP_systick_add_callback_function(&TASKMGR_process_ms);
	for(uint8_t i = 0; i<NB_MAX_APPLIS ; i++)
		applis[i].enable = false;
}

//cette fonction sera appelée toutes les ms !
static void TASKMGR_process_ms(void)
{
	for(uint8_t i = 0; i<NB_MAX_APPLIS ; i++)
	{
		if(applis[i].enable)
		{
			applis[i].process_ms();
		}
	}
}


running_t TASKMGR_launch_appli(appli_t * appli, uint8_t * id)
{
	running_t ret = END_ERROR;
	for(uint8_t i = 0; i<NB_MAX_APPLIS ; i++)
	{
		if(applis[i].enable == false)
		{
			//on a trouvé une case libre !!! Champomy !!
			applis[i] = *appli;
			applis[i].enable = true;
			applis[i].init();	//on initialise l'application nouvellement lancée !
			*id = i;
			ret = END_OK;
			break;
		}
	}
	return ret;
}

running_t TASKMGR_kill_appli(process_main_fun_t pfun)
{
	running_t ret = END_ERROR;
	for(uint8_t i = 0; i<NB_MAX_APPLIS ; i++)
	{
		if(applis[i].enable == true && applis[i].process_main == pfun)
		{
			applis[i].enable = false;
			ret = END_OK;
			break;
		}
	}
	return ret;
}


running_t TASKMGR_kill_app(uint8_t id)
{
	running_t ret = END_ERROR;
	if(id < NB_MAX_APPLIS && applis[id].enable == true)
	{
		applis[id].enable = false;
		ret = END_OK;
	}
	return ret;
}

//permet de demander poliment à une application qu'elle se termine d'elle même !
void TASKMGR_ask_for_end(uint8_t id)
{
	running_t ret = END_ERROR;
	if(id < NB_MAX_APPLIS && applis[id].enable == true)
	{
		applis[id].ask_for_end();
		ret = END_OK;
	}
	return ret;
}

//cette fonction devra être appelée dans la boucle de tâche de fond (while(1)) !!!
void TASKMGR_process_main(void)
{
	for(uint8_t i = 0; i<NB_MAX_APPLIS ; i++)
	{
		if(applis[i].enable)
		{
			switch(applis[i].process_main())
			{
				case IN_PROGRESS:
				    ILI9341_PutsCenter(WIDTH/2,HEIGHT/2, "appli is running", &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
					break;
				case END_OK:
					applis[i].enable = false;
				    ILI9341_PutsCenter(WIDTH/2,HEIGHT/2, "appli is closed (success)", &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
					printf("appli %d is closed (success)\n", i);
					break;
				case END_ERROR:
					applis[i].enable = false;
				    ILI9341_PutsCenter(WIDTH/2,HEIGHT/2, "appli is closed (fail)", &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
					printf("appli %d is closed (fail)\n", i);
					break;
				case END_TIMEOUT:
					applis[i].enable = false;
				    ILI9341_PutsCenter(WIDTH/2,HEIGHT/2, "appli is closed (timeout)", &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
					printf("appli %d is closed (timeout)\n", i);
					break;
				default:
					break;
			}
		}
	}
}
