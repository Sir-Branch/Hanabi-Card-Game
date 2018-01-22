/* 
 * File:   event_handler_allegro.cpp
 * Author: r2d2
 *
 * Created on February 12, 2017, 9:29 AM
 */

#include "event_handler_allegro.h"
#include <allegro5/allegro_native_dialog.h>

void event_handle_allegro(ALLEGRO_EVENT ev, hanabi_game_data_t * hanabi_game_data, std::queue<hanabi_game_event_t> *button_event_queue)
{
	if(ev.type == ALLEGRO_EVENT_TIMER) 
	{
		if(ev.timer.source == hanabi_game_data->fps_timer)
			hanabi_game_data->redraw = true;
		else if(ev.timer.source == hanabi_game_data->network_timer)
			hanabi_game_data->check_connection = true;
	}
	else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)//Si se cierra el display o click de mouse cerrar
	{
		if ( al_show_native_message_box( hanabi_game_data->display,
			"Trying to escape?", "Exit Game", "Are you sure you wish to exit the great game?",
			NULL, ALLEGRO_MESSAGEBOX_YES_NO) == 1)
			hanabi_game_data->do_exit = true;
	}
	else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) 
		hanabi_game_data->active_menu->update_buttons(hanabi_game_data->display,ev.mouse.x, ev.mouse.y);
	else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		hanabi_game_data->active_menu->check_for_click(hanabi_game_data->display,ev.mouse.x, ev.mouse.y, *button_event_queue);
	else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		hanabi_game_data->active_menu->manage_keyboard_stroge(ev.keyboard.keycode);//EVENT_HANDLE_ALLEGRO_KEYBOARD???
	
#warning "Change event queue to pointer"
}
