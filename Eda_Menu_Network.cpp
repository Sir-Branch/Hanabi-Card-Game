/* 
 * File:   Eda_Menu_Network.cpp
 * Author: r2d2
 * 
 * Created on March 9, 2017, 2:55 PM
 */

#include "Eda_Menu_Network.h"
#include "Eda_Button.h"

//Para eda Menu game
#include "Eda_Menu_Game.h"


Eda_Menu_Network::Eda_Menu_Network() {
	
	connect =  new Eda_Button( 0.7, 0.9, 0.045 * 3.75, 0.08, "connect.png", "connect_hover.png", NULL, EDA_BUTTON_CANCEL_PRESSED);
	cancel = new Eda_Button(0.9, 0.9, 0.045 * 3.75, 0.08, "cancel.png", "cancel_hover.png", NULL, EDA_BUTTON_CANCEL_PRESSED );

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

	return click_button;
}