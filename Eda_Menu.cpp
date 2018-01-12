/* 
 * File:   Eda_Menu.cpp
 * Author: r2d2
 * 
 * Created on January 14, 2017, 10:27 PM
 */

#include "Eda_Menu.h"

Eda_Menu::Eda_Menu() {
}

Eda_Menu::Eda_Menu(const Eda_Menu& orig) {
}

Eda_Menu::~Eda_Menu() {
}

void Eda_Menu::manage_keyboard_stroge(unsigned int allegro_key)
{
	
}

void Eda_Menu::draw_font(ALLEGRO_DISPLAY * display, const char * font_name, float x_center , float y_center,
				float y_size_percent, const char * text, ALLEGRO_COLOR color)
{
	ALLEGRO_FONT * font_to_draw;
	unsigned int font_size = y_size_percent * al_get_display_height(display); //cast to int
	font_to_draw = al_load_font(font_name, font_size, 0);
	al_draw_text(font_to_draw, color , x_center * al_get_display_width(display), y_center * al_get_display_height(display) - font_size/2, ALLEGRO_ALIGN_CENTRE , text);
	al_destroy_font(font_to_draw);
}