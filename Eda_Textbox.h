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
#include <string>

typedef enum{ NICKNAME_MODE, NUMBERS_ONLY_MODE, IP_MODE}textbox_modes_t;



#define	FONT_TEXTBOX	"DroidSansMono.tff"
#define BLINK_CHAR	'>'
#define BLINK_FPS_RATE		15	
#define BLINK_ON_FPS_RATE	15

class Eda_Textbox : public Eda_Button {
public:
	Eda_Textbox();
	Eda_Textbox(float x_center , float y_center ,float x_size_percent , float y_size_percent, const char * fill_image,
				const char * hover_image, const char * selection_image, event_button_t generated_event_click,
				unsigned int max_characters);
	Eda_Textbox(const Eda_Textbox& orig);
	virtual ~Eda_Textbox();
	void add_char_allegro(unsigned int allegro_key, textbox_modes_t textbox_mode);
	bool load_mono_font(ALLEGRO_DISPLAY * display, char * path);
	virtual void draw(ALLEGRO_DISPLAY * display);
	std::string get_text_buffer(void);
	virtual void deselect();// Needs to remove blinker when not selected

protected:
	void blink_input_char(unsigned int on_fps_rate, unsigned int on_fps_length);
	ALLEGRO_FONT * font;
	char * text_buffer;
	unsigned int text_buffer_size;
	unsigned int num_in_buffer;
	bool blink_placed;
	
	unsigned int count;
	unsigned int on_count;

	

};

#endif /* EDA_TEXTBOX_H */

