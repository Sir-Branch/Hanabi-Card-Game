/* 
 * File:   Eda_Textbox.cpp
 * Author: r2d2
 * 
 * Created on April 5, 2017, 7:22 PM
 */

#include "Eda_Textbox.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_color.h>

Eda_Textbox::Eda_Textbox(const Eda_Textbox& orig) {
}

Eda_Textbox::~Eda_Textbox() {
	
	delete [] this->text_buffer;
	blink_placed = false;
	if(font != NULL)
		al_destroy_font(this->font);
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
	this->font = NULL;
		
}

void Eda_Textbox::add_char_allegro(unsigned int allegro_key, bool only_numbers)
{
	bool add_char = false;
	char char_to_add ='\0';
	
	if(allegro_key == ALLEGRO_KEY_BACKSPACE && 
		(this->num_in_buffer > 0 && !blink_placed || this->num_in_buffer > 1 && blink_placed)
		)
	{
		num_in_buffer--;
	}
	else if(this->num_in_buffer >= this ->text_buffer_size)
	{
		;//Unable to add char because it's full
	}
	else if(!only_numbers && allegro_key >= ALLEGRO_KEY_A && allegro_key <= ALLEGRO_KEY_Z)
	{
		add_char = true;
		char_to_add = allegro_key - ALLEGRO_KEY_A + 'A';
	}
	else if( allegro_key >= ALLEGRO_KEY_0 && allegro_key <= ALLEGRO_KEY_9 )
	{
		add_char = true;
		char_to_add = allegro_key - ALLEGRO_KEY_0 + '0';
	}
	else if( allegro_key == ALLEGRO_KEY_FULLSTOP)
	{
		add_char = true;
		char_to_add  = '.';
	}
	
	if(add_char)
	{
		if(blink_placed)
		{
			num_in_buffer--;
			text_buffer[num_in_buffer++] = char_to_add;
			text_buffer[num_in_buffer++] = BLINK_CHAR;
		}
		else
		{
			text_buffer[num_in_buffer++] = char_to_add;
		}
	}

	text_buffer[num_in_buffer] = '\0';
}

bool Eda_Textbox::load_mono_font(ALLEGRO_DISPLAY * display, char * path)
{
	unsigned int i;
	bool error = false;
	unsigned int max_height = al_get_display_height(display) * this->x_size_percent;
	unsigned int max_width  = al_get_display_width(display)  * this->y_size_percent;
	for(i = 2; ; i = i + 2 )
	{
		this->font = al_load_ttf_font(path,i,0);
		if( al_get_font_line_height(this->font) > max_height || 
			0.5 * al_get_text_width(this->font, "a") * this->text_buffer_size > max_width)
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

void Eda_Textbox::draw(ALLEGRO_DISPLAY * display)
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
		blink_input_char(BLINK_FPS_RATE, BLINK_ON_FPS_RATE);
		al_draw_text(this->font, al_color_name("white"), 
					x_center * al_get_display_width(display) - x_size_percent * al_get_display_width(display) *0.45, 
					y_center * al_get_display_height(display) - al_get_font_line_height(this->font)/2, 
					ALLEGRO_ALIGN_LEFT, this->text_buffer);
		
	} 
	
	
}



void Eda_Textbox::blink_input_char(unsigned int on_fps_rate, unsigned int on_fps_length)
{
	static int count = 0;
	static int on_count = 0;
	count++;
	
	if( this->blink_placed == false && count % on_fps_rate == 0)
	{
		count = 0;
		this->blink_placed = true;
		this->text_buffer[num_in_buffer++] = BLINK_CHAR;
		this->text_buffer[num_in_buffer] = '\0';
		
	}
	else if( blink_placed == true && ++on_count % on_fps_length == 0)
	{
		on_count = 0;
		count = 0;
		this->blink_placed = false;
		this->text_buffer[--num_in_buffer] = '\0';
	}
	
}


