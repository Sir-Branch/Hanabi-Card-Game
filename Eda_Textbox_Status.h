/* 
 * File:   Eda_Textbox_Status.h
 * Author: r2d2
 *
 * Created on January 23, 2018, 6:57 PM
 */

#ifndef EDA_TEXTBOX_STATUS_H
#define EDA_TEXTBOX_STATUS_H

#include "Eda_Textbox.h"
#include <string>
#include <list>
#define MESSAGES_TO_SHOW	4

class Eda_Textbox_Status : public Eda_Textbox {
public:
	Eda_Textbox_Status(float x_center , float y_center ,float x_size_percent , float y_size_percent, const char * fill_image,
				const char * hover_image, const char * selection_image, event_button_t generated_event_click,
				unsigned int max_characters);
	virtual void draw(ALLEGRO_DISPLAY * display);
	virtual ~Eda_Textbox_Status();
	
	bool load_mono_font(ALLEGRO_DISPLAY * display, char * path);
	void add_message(std::string message);
	void remove_message(unsigned int num_message);
private:

	std::list< std::string> messages;
	//Eda_Textbox_Status(const Eda_Textbox_Status& orig);

};

#endif /* EDA_TEXTBOX_STATUS_H */

