#include "config.h"
#include "stm32g4_sys.h"

#include "stm32g4_systick.h"
#include "stm32g4_gpio.h"
#include "stm32g4_uart.h"
#include "tft_ili9341/stm32g4_ili9341.h"
#include "Ui/ui.h"
#include "taskmgr.h"

#include <stdio.h>

#include "mon_appli.h"


/*
// Déclaration des apps existantes
extern app_t mon_appli;

// Table des apps disponibles
app_t* app_list[] = {
    &mon_appli
    // ajouter plus tard : , &app_clock, &app_notes, ...
};

#define APP_COUNT (sizeof(app_list)/sizeof(app_t*))

// Index de l’app actuellement sélectionnée
static int selected_index = 0;

void app_menu_init(void) {
    selected_index = 0;
    ILI9341_Fill(ILI9341_COLOR_BLACK); // Nettoyage écran
}

void app_menu_process_main(void) {
    // Gérer l’appui sur le bouton
    if (button_press_event(GPIOA,GPIO_PIN_15,1)) {
        selected_index++;
        if (selected_index >= APP_COUNT) {
            selected_index = 0; // on boucle
        }

        // Réafficher le nom de l’app sélectionnée
        ILI9341_Fill(ILI9341_COLOR_BLACK);
        ILI9341_PutsCenter(20, 100, app_list[selected_index]->name,ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK, 2);
    }
}

void app_menu_process_ms(void) {
    // pas nécessaire pour l’instant
}

appli_t app_menu = {
    .init = app_menu_init,
    .process_main = app_menu_process_main,
    .process_ms = app_menu_process_ms,
    .name = "Menu"
};
*/



