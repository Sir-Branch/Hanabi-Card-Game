/* 
 * File:   event_handler_allegro.cpp
 * Author: r2d2
 *
 * Created on February 12, 2017, 9:29 AM
 */

#include "event_handler_allegro.h"

void event_handle_allegro(ALLEGRO_EVENT ev, hanabi_game_data_t * hanabi_game_data, std::queue<hanabi_game_event_t> *button_event_queue)
{
	if(ev.type == ALLEGRO_EVENT_TIMER) // por que tenemos un timer para redibujar?
		hanabi_game_data->redraw = true;
	else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)//Si se cierra el display o click de mouse cerrar
		hanabi_game_data->do_exit = true;
	else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) 
		hanabi_game_data->active_menu->update_buttons(hanabi_game_data->display,ev.mouse.x, ev.mouse.y);
	else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		hanabi_game_data->active_menu->check_for_click(hanabi_game_data->display,ev.mouse.x, ev.mouse.y, *button_event_queue);
	else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		;//EVENT_HANDLE_ALLEGRO_KEYBOARD???
	
#warning "Change event queue to pointer"
}
