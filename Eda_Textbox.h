/* 
 * File:   Eda_Textbox.h
 * Author: r2d2
 *
 * Created on April 5, 2017, 7:22 PM
 */

#ifndef EDA_TEXTBOX_H
#define EDA_TEXTBOX_H

#include "Eda_Button.h"

#warning "Rethink text_box max text size on construct? Or calculate based on the font size???/"
class Eda_Textbox : Eda_Button {
public:
	Eda_Textbox();
	Eda_Textbox(float x_center , float y_center ,float x_size_percent , float y_size_percent, const char * fill_image,
				const char * hover_image, const char * selection_image, event_button_t generated_event_click); 
	Eda_Textbox(const Eda_Textbox& orig);
	virtual ~Eda_Textbox();
	
private:
	
	char * text_buffer;
	unsigned int text_buffer_size;
	
	

};

#endif /* EDA_TEXTBOX_H */

