/* 
 * File:   Hanabiboard.h
 * Author: r2d2
 *
 * Created on July 25, 2016, 7:25 PM
 */

#ifndef HANABIBOARD_H
#define HANABIBOARD_H

#include "Hanabi_Card.h"
#include "Deck.h"
#include "Token.h"
#include "Hanabi_Deck.h"
#include "TFTPCxn.h"
#include "Hanabi_Start_Info_Packet.h"
#include "Networking.h"



#define HANABI_LIGHT_TOKENS		3	//Numb of "lifes" 
#define HANABI_CLUE_TOKENS		9	//Numb of clue tokens
#define HANABI_NUMBER_COLORS	5	//Yeah colors, the u is only if u are British 
#define HANABI_CARDS_PER_HAND	6	//Numb cards per hand
#define MAX_SCORE				25


//The suit of each card has a position for the central array use get_suit_number_array


class Hanabi_Board{
public:
    Hanabi_Board();
	
	//Clues methods 
    bool any_clues_left(void); //Returns true if there are any clues left, see more comments in .cpp
    bool all_clues_left(void); //Returns true if there are all clues left, see more comments in .cpp
    bool add_clue_token(void); //Adds a clue token. Returns true if it was successfull, see more comments in .cpp
    unsigned int number_clues_left(void); //Returns number of clues left, see more comments in .cpp
    bool validate_give_clue(unsigned char value_or_suit); //Checks the clue before sending it to the other player, see more comments in .cpp
    
	//Lives methods
    bool any_lives_left(void); //Returns true if there are any lifes left, see more comments in .cpp
    unsigned int number_lives_left(void); //Returns the number of lives left, see more comments in .cpp
	
    //Players methods 
    bool player_action_play_card(unsigned int card_my_hand); 
    void player_action_discard_card(unsigned int card_my_hand);
	void player_action_give_clue(unsigned char value_or_suit);
	std::string other_player_name;	
#warning "Cambiar el uso de other_player_name al de game_data hay que cambiar la funcion draw para que reciba game_data"
#warning "Falta probar give clue"
	
    //Actions received methods
    void receive_action_draw_card(Hanabi_Card card);
    void receive_action_play_card(unsigned int card_other_hand);
    void receive_action_discard_card(unsigned int card_other_hand);
    void receive_action_get_clue(unsigned char value_or_suit);//player can only "receive" one action which is a clue
	
    void print_my_hand(void); //Funcion de debug se puede borrar. 
	unsigned int calculate_score(void);
    

    
#warning "After testing switch to private"
public://Public for testing functions
	
	bool start_game(void);
	void receive_start_game(const char * start_pck);
    
    bool remove_clue_token(void); //Removes a clue token. Returns true if it was successfull, see more comments in .cpp
	void lose_live(void);
	
    bool can_place_card(unsigned int card_my_hand);
	bool can_other_place_card(unsigned int card_others_hand);
    bool draw_card(unsigned int card_my_hand);
    void discard_card(unsigned int card_my_hand);
	void discard_others_card(unsigned int card_others_hand);

	
    Hanabi_Deck hanabi_game_deck;
    Deck<Hanabi_Card> grave_yard[HANABI_NUMBER_COLORS]; // Uno por color
    Token light_tokens[HANABI_LIGHT_TOKENS];//Representan las vidas 
    Token clue_tokens[HANABI_CLUE_TOKENS];//Maxima numero de pistas que se pueden dar sin tomar carta

   
    Hanabi_Card central_cards[HANABI_NUMBER_COLORS];//De aca se ven las pilas (convendra usarlas como card ya que solamente se ve la de arriba)
	//Convendra usar una de ints del 0 al 5??
    Hanabi_Card otherplayers_hand[HANABI_CARDS_PER_HAND];
    unsigned int otherplayers_card_replace; // Card to be replaced on draw. 	
    unsigned int my_card_replace; // Card to be replaced on draw. 	
    in_game_hanabi_Card_t my_cards[HANABI_CARDS_PER_HAND];	
    bool last_hand; //True if deck is empty. 
    bool lost_game; //True if the game is lost. 
    unsigned int score; // Score from 0 a 25.
};

#endif /* HANABIBOARD_H */

