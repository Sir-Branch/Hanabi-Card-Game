/* 
 * File:   Eda_Button.h
 * Author: r2d2
 *
 * Created on January 14, 2017, 10:26 PM
 */

#ifndef EDA_BUTTON_H
#define EDA_BUTTON_H

#include <allegro5/allegro5.h>
#include "hanabi_events.h"

class Eda_Button{
public:
	Eda_Button();
	Eda_Button(float x_center , float y_center ,float x_size_percent , float y_size_percent, const char * fill_image,
				const char * hover_image, const char * selection_image, event_button_t generated_event_click);
	virtual ~Eda_Button();
	
	void draw(ALLEGRO_DISPLAY * display);
	
	bool update_hovering(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse);
	bool check_mouse_over(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse);//useful for detecting clicks 
	bool check_mouse_over_click(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse);
	bool check_mouse_over_toggle(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse);
	
	virtual void select(void);
	virtual void deselect(void);
	bool is_selected(void);

	bool is_hidden(void);
	void hide(void);
	void show(void);
	hanabi_game_event_t get_click_event(void);
	//void set_hovering(bool hovering);
	float x_center , y_center; 
	float x_size_percent , y_size_percent; //Percentage of display size, this allows for same button size across various resolutions	
protected:
	Eda_Button(const Eda_Button& orig);
	//This must be from 0 to 1.0 and represents the percentage of screen, this allows for correct placement on various resolutions

	
	
	ALLEGRO_BITMAP * fill_image;
	ALLEGRO_BITMAP * fill_hover_image; //On hover will always draw fill_image and hover on top just incase hover is a border
	ALLEGRO_BITMAP * fill_selection_image;//On selection will always draw fill_image and selection on top just incase selection is aborder
	//If selected hover will not be drawn
	
	bool hidden;//If true button will be hidden
	
	bool hover_option; //If true, then on hover option will be displayed
	bool hovering;
	
	bool selection_option;//might be easiest way to use for game buttons
	bool selected;
	
	event_button_t generated_event_click;
	
};

#endif /* EDA_BUTTON_H */

