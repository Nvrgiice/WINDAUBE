/*
 * ui.c
 *
 *  Created on: Apr 9, 2025
 *      Author: Hippo
 */


#include "tft_ili9341/stm32g4_ili9341.h"
#include "../button/button.h"
#include "tft_ili9341/stm32g4_xpt2046.h"
#include "stm32g4_gpio.h"
#include "../app_menu/app_menu.h"
#define WIDTH 320
#define HEIGHT 240



void startanim(void){

	ILI9341_Init();

	ILI9341_Fill(ILI9341_COLOR_BLACK);
	ILI9341_DrawFilledCircle(WIDTH/2, HEIGHT/2, 50, ILI9341_COLOR_BLUE);
	HAL_Delay(1000);
	ILI9341_Fill(ILI9341_COLOR_BLACK);
	ILI9341_PutsCenter(WIDTH/2,HEIGHT/2, "bienvenue", &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
	HAL_Delay(3000);
	//app_start(&app_menu); //pour + tard
	afficher_menu();


}



/*
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
*/

void stopanim(void) {

	ILI9341_Init();

	ILI9341_Fill(ILI9341_COLOR_BLACK);
	ILI9341_PutsCenter(WIDTH/2,HEIGHT/2, "extinction", &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
	HAL_Delay(5000);
	ILI9341_Fill(ILI9341_COLOR_BLACK);


}

// Affichage du menu
void afficher_menu(void) {
    // Effacer l'écran
    ILI9341_Fill(ILI9341_COLOR_BLACK);

    // Afficher les boutons "Editeur" et "Explorateur"
    ILI9341_PutsCenter(WIDTH / 4, HEIGHT/2 +50, "Editeur", &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
    ILI9341_PutsCenter(WIDTH * 3 / 4, HEIGHT/2 +50, "Explorateur", &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);

    // Dessiner des rectangles autour des boutons pour les zones tactiles
    ILI9341_DrawRectangle(0, 0, WIDTH / 2, HEIGHT, ILI9341_COLOR_WHITE);
    ILI9341_DrawRectangle(WIDTH / 2, 0, WIDTH, HEIGHT, ILI9341_COLOR_WHITE);
}



// Gestion des événements tactiles
void gestion_tactile(void) {

	ILI9341_Puts(0,0,"tactile",&Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);

    uint16_t x, y;
    if(XPT2046_getMedianCoordinates(&x, &y, XPT2046_COORDINATE_SCREEN_RELATIVE)) {
        if ((x > 0 && x < WIDTH / 4 + 80 && y > 0 / 2 - 40 && y < HEIGHT / 2)) {
            ouvrir_editeur();
        } else if ((x > 0 && x < WIDTH && y > HEIGHT / 2 && y < HEIGHT)) {
            ouvrir_explorateur();
        }
    }

}

// Ouvrir l'éditeur de texte
void ouvrir_editeur(void) {
    ILI9341_Fill(ILI9341_COLOR_BLACK);
    ILI9341_DrawFilledRectangle(0,0,WIDTH,50,ILI9341_COLOR_YELLOW);
    ILI9341_PutsCenter(WIDTH / 2, 20, "Editeur de texte", &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_YELLOW);
    // Ajouter logique éditeur
}

// Ouvrir l'explorateur de fichiers
void ouvrir_explorateur(void) {
    ILI9341_Fill(ILI9341_COLOR_BLACK);
    ILI9341_DrawFilledRectangle(0,0,WIDTH,50,ILI9341_COLOR_GREEN);
    ILI9341_PutsCenter(WIDTH / 2, 20, "Explorateur de fichiers", &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_GREEN);
    // Ajouter logique explorateur
}

