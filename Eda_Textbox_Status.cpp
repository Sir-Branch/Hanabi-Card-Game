/* 
 * File:   Eda_Textbox_Status.cpp
 * Author: r2d2
 * 
 * Created on January 23, 2018, 6:57 PM
 */

#include "Eda_Textbox_Status.h"
#include <list>
#include <string>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_color.h>

//Eda_Textbox(float x_center , float y_center ,float x_size_percent , float y_size_percent, const char * fill_image,
//				const char * hover_image, const char * selection_image, event_button_t generated_event_click,
//				unsigned int max_characters)
Eda_Textbox_Status::Eda_Textbox_Status(float x_center , float y_center ,float x_size_percent , float y_size_percent, const char * fill_image,
				const char * hover_image, const char * selection_image, event_button_t generated_event_click,
				unsigned int max_characters)
				:Eda_Textbox(x_center , y_center , x_size_percent ,  y_size_percent,  fill_image,
				hover_image,selection_image, generated_event_click,
				max_characters)
{
	
}

//Eda_Textbox_Status::Eda_Textbox_Status(const Eda_Textbox_Status& orig) {
//}

Eda_Textbox_Status::~Eda_Textbox_Status() {
}

void Eda_Textbox_Status::add_message(std::string message_to_add)
{
	messages.push_back(message_to_add);
	if( messages.size() > MESSAGES_TO_SHOW)
		messages.pop_front();
	
}

void Eda_Textbox_Status::remove_message(unsigned int num_message){
	
	if( num_message  <= messages.size() )
	{
		std::list<std::string>::iterator it = messages.begin();
		std::advance (it,num_message); //0 is first element
		messages.erase(it);
	}
	
}

bool Eda_Textbox_Status::load_mono_font(ALLEGRO_DISPLAY * display, char * path)
{
	unsigned int i;
	bool error = false;
	unsigned int max_height = al_get_display_height(display) * this->x_size_percent;
	unsigned int max_width  = al_get_display_width(display)  * this->y_size_percent;
	for(i = 2; ; i = i + 2 )
	{
		this->font = al_load_ttf_font(path,i,0);
		if( al_get_font_line_height(this->font) * MESSAGES_TO_SHOW  > max_height || 
			( al_get_text_width(this->font, "a") * this->text_buffer_size > max_width) )
		{
			al_destroy_font(this->font);
			break;
		}
		al_destroy_font(this->font);
	}
	i = i - 2;
	
	if(i < 2)
		error = true;
	else
		this->font = al_load_ttf_font(path,i,0);
	
}

void Eda_Textbox_Status::draw(ALLEGRO_DISPLAY * display)
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
		
		std::list<std::string>::iterator it;
		int i;
		for(it = messages.begin(), i = 0 ; it != messages.end() ; it++, i++)
			al_draw_text(this->font, al_color_name("dark grey"), 
						x_center * al_get_display_width(display) - x_size_percent * al_get_display_width(display) *0.45, 
						y_center * al_get_display_height(display) //- al_get_font_line_height(this->font)/2 
						- al_get_font_line_height(this->font) * (MESSAGES_TO_SHOW/2-i), 
						ALLEGRO_ALIGN_LEFT, (*it).c_str());
		
	} 
}

