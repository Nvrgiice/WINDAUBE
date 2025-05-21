#include "stm32g4_sys.h"
#include "taskmgr.h"
#include "tft_ili9341/stm32g4_ili9341.h"

#define WIDTH 320
#define HEIGHT 240

static uint32_t compteur = 0;

void MON_APPLI_init(void) {
    compteur = 0;
    ILI9341_Init();
    printf("init app");
    //ILI9341_Fill(ILI9341_COLOR_GREEN);
    //ILI9341_PutsCenter(WIDTH/2,HEIGHT/2, "init app", &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
}

void MON_APPLI_process_ms(void) {
    //ILI9341_PutsCenter(WIDTH/2,HEIGHT/2, "Mon_App_process_ms en process", &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
    compteur++;
}

running_t MON_APPLI_process_main(void) {
    if (compteur > 10000) {
        return END_OK; // Ferme l'appli après 10000 ms
    }
    ILI9341_Fill(ILI9341_COLOR_GREEN);
    return IN_PROGRESS;
}

void MON_APPLI_ask_for_end(void) {
	ILI9341_Init();
	printf("fermeture app");
    ILI9341_PutsCenter(WIDTH/2,HEIGHT/2, "fermeture app", &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
    compteur = 10001; // forcera la fermeture
}
