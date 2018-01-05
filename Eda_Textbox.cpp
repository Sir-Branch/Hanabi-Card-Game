/* 
 * File:   Eda_Textbox.cpp
 * Author: r2d2
 * 
 * Created on April 5, 2017, 7:22 PM
 */

#include "Eda_Textbox.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

Eda_Textbox::Eda_Textbox(const Eda_Textbox& orig) {
}

Eda_Textbox::~Eda_Textbox() {
	
	delete [] this->text_buffer;
}


Eda_Textbox::Eda_Textbox(float x_center , float y_center ,float x_size_percent , float y_size_percent, const char * fill_image,
				const char * hover_image, const char * selection_image, event_button_t generated_event_click,
				unsigned int max_characters)
			:Eda_Button(x_center, y_center, x_size_percent, y_size_percent, fill_image, hover_image, selection_image, generated_event_click)
{
	this->text_buffer = new char[max_characters];
	this->text_buffer_size = max_characters;
	this->num_in_buffer = 0;
	this->text_buffer[this->num_in_buffer] = '\0';
	
}

void Eda_Textbox::add_char_allegro(unsigned int allegro_key, bool only_numbers)
{
	if(!only_numbers && allegro_key >= ALLEGRO_KEY_A && allegro_key <= ALLEGRO_KEY_Z)
	{
		text_buffer[num_in_buffer]= allegro_key - ALLEGRO_KEY_A + 'A';
		num_in_buffer++;
	}
	else if( allegro_key >= ALLEGRO_KEY_0 && allegro_key <= ALLEGRO_KEY_0 )
	{
		text_buffer[num_in_buffer]= allegro_key - ALLEGRO_KEY_0 + '0';
		num_in_buffer++;
	}
	else if(allegro_key == ALLEGRO_KEY_BACKSPACE)
	{
		num_in_buffer--;
	}
	text_buffer[num_in_buffer]= '\0';

}

bool Eda_Textbox::load_mono_font(char * path,ALLEGRO_DISPLAY * display)
{
	unsigned int i;
	bool error = false;
	unsigned int max_height = al_get_display_height(display) * this->x_size_percent;
	unsigned int max_width  = al_get_display_width(display)  * this->y_size_percent;
	for(i = 2; ; i = i + 2 )
	{
#warning fix
		this->font = al_load_ttf_font(path,i,0);
		if( al_get_font_line_height(this->font) > max_height )//|| 
			//al_get_glyph_width(this->font, 1) * this->text_buffer_size > max_width)
			break;
	}
	i = i -2;
	
	if(i < 2)
		error = true;
	
	
}
