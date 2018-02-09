/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Eda_Menu_Waiting_Connecction.cpp
 * Author: parallels
 * 
 * Created on January 31, 2018, 9:10 AM
 */

#include "Eda_Menu_Waiting_Connecction.h"
#include "setting_management.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>


Eda_Menu_Waiting_Connecction::Eda_Menu_Waiting_Connecction(std::string theme) {
	
	cancel=new Eda_Button(0.5, 0.6, 0.10, 0.08 ,(COMMON_FILE_PATH "/quit.png"), (COMMON_FILE_PATH "/quit_glow.png"), NULL, EDA_BUTTON_CANCEL_PRESSED);
}
Eda_Menu_Waiting_Connecction::Eda_Menu_Waiting_Connecction() {}

Eda_Menu_Waiting_Connecction::~Eda_Menu_Waiting_Connecction() {
	delete cancel;
}

void Eda_Menu_Waiting_Connecction::draw(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme, Hanabi_Board *game_board, bool mem_help)
{
	al_draw_filled_rounded_rectangle( 0.1 * al_get_display_width(display) , 
							  0.1 * al_get_display_height(display),
							  0.9	* al_get_display_width(display), 
							  0.9 * al_get_display_height(display),
							  15, 15, al_map_rgba(0,0,0,200));
	
	cancel->draw(display);
	al_flip_display();
}

void Eda_Menu_Waiting_Connecction::update_buttons(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse)
{
		cancel->update_hovering(display,x_mouse, y_mouse);
}
bool Eda_Menu_Waiting_Connecction::check_for_click(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse, std::queue<hanabi_game_event_t> &button_event_queue)
{
	bool clicked = true;
	
	if(cancel->check_mouse_over(display,x_mouse,y_mouse))
		button_event_queue.push(cancel->get_click_event());\
	else
			clicked = false;
	
	return clicked;
}

