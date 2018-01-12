/* 
 * File:   Eda_Menu_Network.cpp
 * Author: r2d2
 * 
 * Created on March 9, 2017, 2:55 PM
 */

#include "Eda_Menu_Network.h"
#include "Eda_Button.h"
#include "Eda_Textbox.h"
#include "setting_management.h"
#include <allegro5/allegro_color.h>
//Para eda Menu game
#include "Eda_Menu_Game.h"


Eda_Menu_Network::Eda_Menu_Network(ALLEGRO_DISPLAY * display, char * path) {
	
#warning "Connect and cancel deleted for join and host"
	
	connect =  new Eda_Button( 0.7, 0.9, 0.045 * 3.75, 0.08, COMMON_FILE_PATH "/join.png", COMMON_FILE_PATH "/join_hover.png", NULL, EDA_BUTTON_JOIN_PRESSED);
	cancel = new Eda_Button(0.9, 0.9, 0.045 * 3.75, 0.08, COMMON_FILE_PATH "/host.png", COMMON_FILE_PATH "/host_hover.png", NULL, EDA_BUTTON_HOST_PRESSED );
	ip_input = new Eda_Textbox(0.25,0.5, 0.35, 0.15, COMMON_FILE_PATH"/text_box.png",NULL,COMMON_FILE_PATH "/text_box_selected.png",NO_EVENT, 20);
	name_input = new Eda_Textbox(0.75,0.5, 0.35, 0.15, COMMON_FILE_PATH "/text_box.png",NULL,COMMON_FILE_PATH "/text_box_selected.png",NO_EVENT, 20);
		
	if(display != NULL && path != NULL)
	{
		ip_input->load_mono_font(display, path);
		name_input->load_mono_font(display, path);
		ip_input->select();
	}	
}

Eda_Menu_Network::Eda_Menu_Network(const Eda_Menu_Network& orig) {
}

Eda_Menu_Network::~Eda_Menu_Network() {
	
	delete connect;
	delete cancel;
}

void Eda_Menu_Network::draw(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme, Hanabi_Board * game_board)
{
	al_draw_scaled_bitmap(theme->connecting_background, 
							0.0, 0.0, al_get_bitmap_width(theme->connecting_background), al_get_bitmap_height(theme->connecting_background),
							0.0, 0.0, al_get_display_width(display), al_get_display_height(display), //x , y cord to draw and width and height to draw
							0); //flags	

	connect->draw(display);
	cancel->draw(display);
	ip_input->draw(display);
	name_input->draw(display);
	draw_font(display,FONT_PATH "/Alien-Encounters-Solid-Regular.ttf", 0.25, 0.30 , 0.08, "IP ADRESS", al_color_name("white"));
	draw_font(display,FONT_PATH "/Alien-Encounters-Solid-Regular.ttf", 0.75, 0.30 , 0.08, "NickName", al_color_name("white"));
	al_flip_display();

	
}
void Eda_Menu_Network::update_buttons(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse)
{
	connect->update_hovering(display,x_mouse,y_mouse);
	cancel->update_hovering(display,x_mouse,y_mouse);
}

bool Eda_Menu_Network::check_for_click(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse, std::queue<hanabi_game_event_t> &button_event_queue)
{		
	bool click_button = false;

	if( connect->check_mouse_over_toggle(display, x_mouse, y_mouse) )
	{
		click_button = true;
		button_event_queue.push( connect->get_click_event() );
	}
	else if( cancel->check_mouse_over_toggle(display, x_mouse, y_mouse) )
	{
		click_button = true;
		button_event_queue.push( cancel->get_click_event() );
	}
	else if( ip_input->check_mouse_over(display, x_mouse, y_mouse))
	{
		ip_input->select();
		click_button = true;
		if(name_input->is_selected())
			name_input->deselect();
	}
	else if( name_input->check_mouse_over(display, x_mouse, y_mouse) )
	{
		name_input->select();
		click_button = true;
		if(ip_input->is_selected())
			ip_input->deselect();
	}
	return click_button;
}

void Eda_Menu_Network::manage_keyboard_stroge(unsigned int allegro_key)
{
	if( ip_input->is_selected() )
		ip_input->add_char_allegro(allegro_key,IP_MODE);
	else if(name_input->is_selected())
		name_input->add_char_allegro(allegro_key,NICKNAME_MODE);
}


const char* Eda_Menu_Network::read_ip_input(void)
{
    return ip_input->get_text_buffer();
}

const char* Eda_Menu_Network::read_name_input(void)
{
	return name_input->get_text_buffer();

}
