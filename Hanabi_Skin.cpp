/* 
 * File:   Hanabi_Skin.cpp
 * Author: r2d2
 * 
 * Created on January 20, 2017, 11:53 PM
 */

#include <sys/stat.h>
#include <string>
#include "Hanabi_Skin.h"


static bool check_folder_exists(const char * folder_name);

Hanabi_Skin::Hanabi_Skin() 
{
	main_menu = NULL;
	connecting_background = NULL;
	game_mat = NULL;
	
	cards_backside = NULL;
	for(unsigned int i = 0 ; i < 5 ; i++)
	{
		cards_blue[i] = NULL;
		cards_green[i] = NULL;
		cards_red[i] = NULL;
		cards_white[i] = NULL;
		cards_yellow[i] = NULL;	
	}

	//0 Will correspond to disable 1 to enabled for tokens
	token_clue[0] = NULL; 
	token_clue[1] = NULL; 
	token_lightning[0] = NULL;
	token_lightning[1] = NULL;
	
	//clue_numbers[5];
	//clue_colors[5];
	//clue_hover = NULL;


}

Hanabi_Skin::~Hanabi_Skin() 
{
	if( this->main_menu != NULL)
		al_destroy_bitmap(this->main_menu);
	if( this->connecting_background != NULL)
		al_destroy_bitmap(this->connecting_background);
	if( this->token_clue[0] != NULL)
		al_destroy_bitmap(this->token_clue[0]);
	if( this->token_clue[1] != NULL)
		al_destroy_bitmap(this->token_clue[1]);
	if( this->token_lightning[0] != NULL)
		al_destroy_bitmap(this->token_lightning[0]);
	if( this->token_lightning[1] != NULL)
		al_destroy_bitmap(this->token_lightning[1]);
	if( this->cards_backside != NULL)
		al_destroy_bitmap(this->cards_backside);
	
	for(unsigned int i = 0 ; i < 5 ; i++)
	{
		if( this->cards_blue[i] != NULL)
			al_destroy_bitmap(this->cards_blue[i]);
		if( this->cards_green[i] != NULL)
			al_destroy_bitmap(this->cards_green[i]);
		if( this->cards_red[i] != NULL)
			al_destroy_bitmap(this->cards_red[i]);
		if( this->cards_white[i] != NULL)
			al_destroy_bitmap(this->cards_white[i]);
		if( this->cards_yellow[i] != NULL)
			al_destroy_bitmap(this->cards_yellow[i]);
	}
}


bool check_folder_exists(const char * folder_name)
{
	struct stat sb;
	return ( stat(folder_name, &sb) == 0 && S_ISDIR(sb.st_mode) );	
}

bool Hanabi_Skin::load_theme(std::string theme_name)
{
	bool success = false;
	std::string current_folder;
	
	if( check_folder_exists( ("Hanabi Themes/" + theme_name).c_str()))
	{
		success = true;
		std::string main_menu, game_mat, connecting_background, token_clue,
			token_lightning, deck;
		
		current_folder =   "Hanabi Themes/" + theme_name + "/";
		
		main_menu = current_folder + "main_menu.png";
		game_mat = current_folder + "game_mat.png";
		connecting_background = current_folder + "connecting_background.png"; 
		token_clue = current_folder + "Token Clue/";
		token_lightning = current_folder + "Token Lightning/";
		deck = current_folder + "Deck/"; 
			
		if( (this->main_menu = al_load_bitmap(main_menu.c_str())) == NULL)
			success = false;
		else if( (this->game_mat = al_load_bitmap(game_mat.c_str())) == NULL)
			success = false;
		else if( (this->connecting_background = al_load_bitmap(connecting_background.c_str())) == NULL)
			success = false;
		else if( (this->token_clue[0] = al_load_bitmap( (token_clue + "disable.png").c_str())) == NULL)
			success = false;
		else if( (this->token_clue[1] = al_load_bitmap( (token_clue + "enable.png").c_str())) == NULL)
			success = false;
		else if( (this->token_lightning[0] = al_load_bitmap( (token_lightning + "disable.png").c_str())) == NULL)
			success = false;
		else if( (this->token_lightning[1] = al_load_bitmap( (token_lightning + "enable.png").c_str())) == NULL)
			success = false;
		else if( (this->cards_backside = al_load_bitmap( (deck + "back.png").c_str())) == NULL)
			success = false;
		else
		{

			std::string toload = deck + "blue" + "0";
			for(unsigned int i = 0 ; i < 5 && success ; i++)
			{
				toload[toload.size()-1]++; //Increases number at end of string deck/blue1 then deck/blue2 etc...
				if( (this->cards_blue[i] = al_load_bitmap((toload+".png").c_str() ) ) == NULL)
					success = false;
			}
			
			toload = deck + "green" + "0";
			for(unsigned int i = 0 ; i < 5 && success ; i++)
			{
				toload[toload.size()-1]++; //Increases number at end of string
				if( (this->cards_green[i] = al_load_bitmap((toload+".png").c_str() ) ) == NULL)
					success = false;
			}
			
			toload = deck + "white" + "0";
			for(unsigned int i = 0 ; i < 5 && success ; i++)
			{
				toload[toload.size()-1]++; //Increases number at end of string
				if( (this->cards_white[i] = al_load_bitmap((toload+".png").c_str() ) ) == NULL)
					success = false;
			}
			
			toload = deck + "red" + "0";
			for(unsigned int i = 0 ; i < 5 && success ; i++)
			{
				toload[toload.size()-1]++; //Increases number at end of string
				if( (this->cards_red[i] = al_load_bitmap((toload+".png").c_str() ) ) == NULL)
					success = false;
			}
			
			toload = deck + "yellow" + "0";
			for(unsigned int i = 0 ; i < 5 && success ; i++)
			{
				toload[toload.size()-1]++; //Increases number at end of string
				if( (this->cards_yellow[i] = al_load_bitmap((toload+".png").c_str() ) ) == NULL)
					success = false;
			}
			
		}
		
	}
	return success;
}

