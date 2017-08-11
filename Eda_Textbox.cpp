/* 
 * File:   Eda_Textbox.cpp
 * Author: r2d2
 * 
 * Created on April 5, 2017, 7:22 PM
 */

#include "Eda_Textbox.h"

Eda_Textbox::Eda_Textbox() {
}

Eda_Textbox::Eda_Textbox(const Eda_Textbox& orig) {
}

Eda_Textbox::~Eda_Textbox() {
}


Eda_Textbox::Eda_Textbox(float x_center , float y_center ,float x_size_percent , float y_size_percent, const char * fill_image,
				const char * hover_image, const char * selection_image, event_button_t generated_event_click)
			:Eda_Button(x_center, y_center, x_size_percent, y_size_percent, fill_image, hover_image, selection_image, generated_event_click)
{
	
	
}