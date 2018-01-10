/* 
 * File:   Eda_button.cpp
 * Author: r2d2
 * 
 * Created on January 14, 2017, 10:26 PM
 */

#include "Eda_Button.h"
#include "hanabi_events.h"

/*
 * Default Constructor
 * To be able to use arrays inside classes and avoid dynamic allocation  
 * Input:"Fonts
 *	-No Input default constructor
 * 
 * Return:
 *	-No return in constructor
 */
Eda_Button::Eda_Button()
{
	this->fill_hover_image = NULL;
	this->fill_image = NULL;
	this->fill_selection_image = NULL;
}
/*
 * Constructor for Eda_Button Initializes all the variables with parameters passed in construction
 * NOTE: all x and y values range from 0 to 1.0, this represents the percent of screen, this allows for
 * different resolutions and screens to look similar 
 * 
 * Input:
 *	-float x_center, y_center: Percent of screen where the center of the button will be placed
 *  -float x_size_percent,y_size_percent: Percent of screen which the button will occupy example x 0.1 and display width 1000, 
 *											the button will have 100 width
 *	-const char * fill_image: path and name from root of project of image which will be used as button
 *	-bool hover_option: True or false if a hover option is desired 
 *	-const char * hover_image: path and name from root of project of image which will be displayed on hover
 *	-event_t generated_event_click: event which will be returned by get_click_event() method. The idea is on a mouse click, check mouse over
 *									(with check_mouse_over method) and if the mouse is clicking button call get_click_event method.
 * 
 * Return:
 *	-No return in constructor
 */
Eda_Button::Eda_Button(float x_center , float y_center ,float x_size_percent , float y_size_percent, const char * fill_image ,
					const char * hover_image, const char * selection_image, event_button_t generated_event_click)
{
	this->fill_image = NULL;
	this->fill_selection_image = NULL;
	this->fill_hover_image = NULL;
	
	this->x_center = x_center;
	this->y_center = y_center;
	this->x_size_percent = x_size_percent;
	this->y_size_percent = y_size_percent;
	this->generated_event_click = generated_event_click;
	
	this->hovering = false;
	this->hover_option = (hover_image != NULL); //if NULL then no hover option
	
	this->selected = false;
	this->selection_option = (selection_image != NULL);
	
	this->hidden = false;
	#warning "Figure out what to do with fail on load bitmap on button"

	if( (this->fill_image = al_load_bitmap(fill_image))== NULL)
		;
	if( hover_option && ((this->fill_hover_image = al_load_bitmap(hover_image)) == NULL) )
		;//Throw exception or what??? 
	if( selection_option && ((this->fill_selection_image = al_load_bitmap(selection_image)) == NULL) )
		;//Throw exception or what??? 
	
}

	


/*
 * Destructor for Eda_Button frees all loaded bitmaps
 * 
 * Input:
 *	-No input in destructor
 * 
 * Return:
 *	-No return in destructor
 */
Eda_Button::~Eda_Button() 
{
	if(fill_image != NULL)
		al_destroy_bitmap(fill_image);
	if(fill_hover_image != NULL)
		al_destroy_bitmap(fill_hover_image);
	if(fill_selection_image != NULL)
		al_destroy_bitmap(fill_selection_image);

}

/*
 * Draw Eda_Button on active display, must pass display to function as percentage of displayed is used in drawing(see constructor)
 * 
 * Input:
 *	-ALLEGRO_DISPLAY * display: Active display, will be used to get width and height
 * 
 * Return:
 *	-Void
 */
void Eda_Button::draw(ALLEGRO_DISPLAY * display)
{
	if( !this->hidden )
	{
		al_draw_scaled_bitmap(fill_image, 
								0.0, 0.0, al_get_bitmap_width(fill_image), al_get_bitmap_height(fill_image),
								(x_center-0.5 * x_size_percent) * al_get_display_width(display), //x_cord to draw
								(y_center-0.5 * y_size_percent) * al_get_display_height(display),  //y_cord to draw
								x_size_percent * al_get_display_width(display), y_size_percent * al_get_display_height(display), //width and height to draw
								0); //flags
		if(selection_option && selected)
			al_draw_scaled_bitmap(fill_selection_image, 
									0.0, 0.0, al_get_bitmap_width(fill_selection_image), al_get_bitmap_height(fill_selection_image),
									(x_center-0.5 * x_size_percent) * al_get_display_width(display), //x_cord to draw
									(y_center-0.5 * y_size_percent) * al_get_display_height(display),  //y_cord to draw
									x_size_percent * al_get_display_width(display), y_size_percent * al_get_display_height(display), //width and height to draw
									0); //flags 
		else if(hover_option && hovering)
			al_draw_scaled_bitmap(fill_hover_image, 
									0.0, 0.0, al_get_bitmap_width(fill_hover_image), al_get_bitmap_height(fill_hover_image),
									(x_center-0.5 * x_size_percent) * al_get_display_width(display), //x_cord to draw
									(y_center-0.5 * y_size_percent) * al_get_display_height(display),  //y_cord to draw
									x_size_percent * al_get_display_width(display), y_size_percent * al_get_display_height(display), //width and height to draw
									0); //flags 
	}
	
}

/*
 * Automatically updated hover status: Checks if mouse is on top of button and sets flag in class
 * 
 * Input:
 *	-ALLEGRO_DISPLAY * display: Active display, will be used to get width and height
 *	-float x_mouse,y_mouse: Mouse x and y cord, will be used in conjunction with display to check mouseover
 * 
 * Return:
 *	-bool: Apart from setting hover returns if hovering or not with bool, 
 *			return will most probably be ignored in implementation.
 */
bool Eda_Button::update_hovering(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse)
{
	if( !hidden && hover_option 
		&& x_mouse >= ((x_center-0.5 * x_size_percent) * al_get_display_width(display)) 
		&& x_mouse <= ((x_center+0.5 * x_size_percent) * al_get_display_width(display)) 
		&& y_mouse >= ((y_center-0.5 * y_size_percent) * al_get_display_height(display))
		&& y_mouse <= ((y_center+0.5 * y_size_percent) * al_get_display_height(display))
		)
		this->hovering = true;
	else
		this->hovering = false;

	return this->hovering;
}

/*
 * Checks if mouse is on top of button
 * 
 * Input:
 *	-ALLEGRO_DISPLAY * display: Active display, will be used to get width and height
 *	-float x_mouse,y_mouse: Mouse x and y cord, will be used in conjunction with display to check mouseover
 * 
 * Return:
 *	-bool: Returns if mouse is on top of button. True mouse if on top, false mouse is not on top of button
 */
bool Eda_Button::check_mouse_over(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse)
{
	return (!hidden && x_mouse >= ((x_center-0.5 * x_size_percent) * al_get_display_width(display)) 
			&& x_mouse <= ((x_center+0.5 * x_size_percent) * al_get_display_width(display)) 
			&& y_mouse >= ((y_center-0.5 * y_size_percent) * al_get_display_height(display))
			&& y_mouse <= ((y_center+0.5 * y_size_percent) * al_get_display_height(display)) );
}

/*
 * Similar to check mouse over, but sets selection if mouse over. 
 * The idea is for this to be called exclusively when a click is generate.
 * 
 * Input:
 *	-ALLEGRO_DISPLAY * display: Active display, will be used to get width and height
 *	-float x_mouse,y_mouse: Mouse x and y cord, will be used in conjunction with display to check mouseover
 * 
 * Return:
 *	-bool: Returns if mouse is on top of button. True mouse if on top, false mouse is not on top of button
 */
bool Eda_Button::check_mouse_over_click(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse)
{
	bool mouse_over = false;
	if (!hidden && x_mouse >= ((x_center-0.5 * x_size_percent) * al_get_display_width(display)) 
		&& x_mouse <= ((x_center+0.5 * x_size_percent) * al_get_display_width(display)) 
		&& y_mouse >= ((y_center-0.5 * y_size_percent) * al_get_display_height(display))
		&& y_mouse <= ((y_center+0.5 * y_size_percent) * al_get_display_height(display)) )
	{
		selected = true;
		mouse_over = true;
	}
	return mouse_over;
}

/*
 * Similar to check mouse over, but toggles selection if mouse over. 
 * The idea is for this to be called exclusively when a click is generate.
 * 
 * Input:
 *	-ALLEGRO_DISPLAY * display: Active display, will be used to get width and height
 *	-float x_mouse,y_mouse: Mouse x and y cord, will be used in conjunction with display to check mouseover
 * 
 * Return:
 *	-bool: Returns if mouse is on top of button. True mouse if on top, false mouse is not on top of button
 */
bool Eda_Button::check_mouse_over_toggle(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse)
{
	bool mouse_over = false;
	if (!hidden && x_mouse >= ((x_center-0.5 * x_size_percent) * al_get_display_width(display)) 
		&& x_mouse <= ((x_center+0.5 * x_size_percent) * al_get_display_width(display)) 
		&& y_mouse >= ((y_center-0.5 * y_size_percent) * al_get_display_height(display))
		&& y_mouse <= ((y_center+0.5 * y_size_percent) * al_get_display_height(display)) )
	{
		selected = !selected;
		mouse_over = true;
	}
	return mouse_over;
}

bool Eda_Button::is_selected(void){
	return selected;
}
/*
 * Deselects a button
 */
void Eda_Button::deselect(void){
	selected = false;
}

/*
 * Selects a button
 */
void Eda_Button::select(void){
	selected = true;
}
/*
 * Returns event, which is intended for when the button is clicked.The idea is on a mouse click, check mouse over
 *	(with check_mouse_over method) and if the mouse is clicking button call get_click_event method.
 * 
 * Input:
 *	-void
 * 
 * Return:
 *	-event_t: Returns the event which is intented for when the button is clicked
 */
hanabi_game_event_t Eda_Button::get_click_event(void)
{
	hanabi_game_event_t event;
	event.type = HANABI_EVENT_BUTTON;
	event.button_event = this->generated_event_click;
	return event;
}

void Eda_Button::show(void)
{
	hidden = false;
}

void Eda_Button::hide(void)
{
	hidden = true;
}

bool Eda_Button::is_hidden(void)
{
	return hidden;
}
