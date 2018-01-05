/* 
 * File:   Eda_Textbox.h
 * Author: r2d2
 *
 * Created on April 5, 2017, 7:22 PM
 */

#ifndef EDA_TEXTBOX_H
#define EDA_TEXTBOX_H

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro5.h>

#include "Eda_Button.h"

#define		FONT_TEXTBOX	"DroidSansMono.tff"

#warning "Rethink text_box max text size on construct? Or calculate based on the font size???"
class Eda_Textbox : Eda_Button {
public:
	Eda_Textbox();
	Eda_Textbox(float x_center , float y_center ,float x_size_percent , float y_size_percent, const char * fill_image,
				const char * hover_image, const char * selection_image, event_button_t generated_event_click,
				unsigned int max_characters);
	Eda_Textbox(const Eda_Textbox& orig);
	virtual ~Eda_Textbox();
	void add_char_allegro(unsigned int allegro_key, bool only_numbers);
	bool load_mono_font(char * path,ALLEGRO_DISPLAY * display);
	
private:
	
	ALLEGRO_FONT * font;
	char * text_buffer;
	unsigned int text_buffer_size;
	unsigned int num_in_buffer;
	

};

#endif /* EDA_TEXTBOX_H */

