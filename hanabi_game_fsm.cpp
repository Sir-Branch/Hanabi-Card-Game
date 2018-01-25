
#if 1
#include "hanabi_game_fsm_callbacks.h"
#include "hanabi_game_fsm.h"
#include "setting_management.h"
	
//***************FOWARD DECLARATIONs******************
// Server
extern STATE main_menu[];
extern STATE connection_menu[];
extern STATE settings_menu[];
extern STATE searching_for_game[];
extern STATE waiting_for_client[];
extern STATE asking_client_name[];
extern STATE ack_client_name_is[];
extern STATE sending_server_name_is[];
extern STATE sending_start_info_client[];
extern STATE defining_start_player[];//SERVER
extern STATE waiting_starting_player[];//CLIENT
// Client
extern STATE connected_to_server[];
extern STATE sending_name_to_server[];
extern STATE waiting_name_server[];
extern STATE waiting_start_info[];
extern STATE validating_start_info[];
extern STATE waiting_starting_player[];
// Both/Gameplay
extern STATE playing[];
extern STATE waiting_other_player_draw[];
extern STATE waiting_other_player[];
extern STATE waiting_action_ack[];
//extern STATE waiting_draw_ack[];

//Finishing Game
extern STATE waiting_receive_result_draw_sent[];
extern STATE playing_last_turn_draw_sent[];
extern STATE waiting_other_player_last_draw_sent[];

extern STATE playing_last_turn_draw_received[];
extern STATE waiting_other_player_last_draw_received[];
extern STATE waiting_receive_result_draw_received[];

extern STATE play_again_quit_menu[];

STATE * get_starting_state(void)
{
	return main_menu;
}

STATE * manage_fsm(STATE * current_state_table,hanabi_fsm_events_t received_event,hanabi_game_data_t *user_data)
{
   	while(current_state_table->event != received_event && current_state_table->event != TABLE_END)
		++current_state_table;
    current_state_table->action(user_data);        //Callback
    return current_state_table->next_state;
}


	
STATE main_menu[]=
{													
	{PLAY_CLICKED, connection_menu,&do_nothing},
    {SETTINGS_CLICK, settings_menu,&do_nothing}, //change resolution music, etc
	{TABLE_END, main_menu, &do_nothing}
  
};

STATE connection_menu[]=
{
	{JOIN_CLICKED, searching_for_game,&do_nothing},
	{HOST_CLICKED, waiting_for_client,&do_nothing},
	{TABLE_END, connection_menu, &do_nothing}

};


STATE settings_menu[]=
{
	{APPLY_CLICKED, main_menu,&do_nothing},
	{CANCEL_CLICKED, main_menu,&do_nothing},
	{TABLE_END, settings_menu, &do_nothing}

};

//****************************************CONNECTION START****************************************************

STATE searching_for_game[]=
{
	
	{FOUND_SERVER,connected_to_server,&do_nothing},
	{SERVER_NOT_FOUND, connection_menu, &do_nothing},
	{TABLE_END, searching_for_game, &do_nothing}
};

//****************************************SERVER STATES****************************************************

STATE waiting_for_client[]=
{
	{CLIENT_CONNECTED, asking_client_name, &send_name_pck},
	{CLIENT_NOT_CONNECTED, connection_menu, &do_nothing},
	{TABLE_END, waiting_for_client, &do_nothing}
	
};


STATE asking_client_name[]=
{
	{RECEIVE_NAME_IS,ack_client_name_is,&manage_name_is_ack},
	{TABLE_END, asking_client_name, &do_nothing}
	
	//{TIMEOUT,asking_client_name,&send_name_pck},
	
	
};

STATE ack_client_name_is[]=
{
	{RECEIVE_NAME , sending_server_name_is, &send_name_is_pck},
	{TABLE_END, ack_client_name_is, &do_nothing}
//	{TIMEOUT, ack_client_name_is, &send_ack_pck}
};

STATE sending_server_name_is[]=
{
	{RECEIVE_ACK , sending_start_info_client,&start_game_send_start_info_pck},
	{TABLE_END, sending_server_name_is, &do_nothing}
	//{TIMEOUT, sending_server_name_is, &send_name_is_pck}

};

STATE sending_start_info_client[]=
{
	{RECEIVE_ACK, defining_start_player, &create_send_random_start},//Will send YOU_START or I_START 
	{TABLE_END, sending_start_info_client, &do_nothing}
	//{RECEIVE_ERROR, manage_error_pck, &do_nothing},
	
	//{TIMEOUT, sending_server_name_is, &send_start_info_pck}

	
};

//Primera jugada del partido es un estado que solo ocurrira una vez
STATE defining_start_player[]=//SERVER
{
	{RECEIVE_ACK, playing	, &do_nothing}, // Fue mandado un I start
	
	//Fue mandado un U_START
	{RECEIVE_PLAY, waiting_other_player_draw, &manage_play_send_ack	},
	{RECEIVE_YOU_HAVE, playing	, &manage_you_have	}, //Si se llega a perder unos de estos paquetes me parece que se cuelga
	{RECEIVE_DISCARD, waiting_other_player_draw,&manage_discard_send_ack  },
	{TABLE_END, defining_start_player, &do_nothing}
	
	//{TIMEOUT,defining_start_player, &resend_random_start}
	
};


STATE waiting_starting_player[]=//CLIENT
{
	{RECEIVE_USTART,playing ,&message_ustart},
	{RECEIVE_ISTART,waiting_other_player,&receive_istart_send_ack},
	{TABLE_END, waiting_starting_player, &do_nothing}
		
};


// ************************ CLIENT STATES ********************************
STATE connected_to_server[]=
{
	{RECEIVE_NAME, sending_name_to_server,&send_name_is_pck},
	{TABLE_END, connected_to_server, &do_nothing}
	
	

};

STATE sending_name_to_server[]=
{
	{RECEIVE_ACK, waiting_name_server ,&send_name_pck},
	{TABLE_END, sending_name_to_server, &do_nothing}
	//{TIMEOUT, sending_name_to_server ,&send_name_is_pck}
	
	

};

STATE waiting_name_server[]=
{
	{RECEIVE_NAME_IS, waiting_start_info,&manage_name_is_ack},
	{TABLE_END, waiting_name_server, &do_nothing}
//	{TIMEOUT, waiting_name_server ,&send_name_pck}

	

};

STATE waiting_start_info[]=
{
	//{RECEIVE_START_INFO, validating_start_info ,&manage_receive_start_info}, //Will generate an Error event or ack 
	{RECEIVE_START_INFO, waiting_starting_player ,&manage_receive_start_info}, //Will generate an Error event or ack 
	{TABLE_END, waiting_start_info, &do_nothing}
};

STATE validating_start_info[]=
{
	{START_INFO_OK, waiting_starting_player, &send_ack_pck},
	{TABLE_END, validating_start_info, &do_nothing}

	//{START_INFO_ERROR, manage_error ,&send_error}, //generated events

};



//*****************************GAME STATES NO CLIENT OR SERVER**********************************************


STATE playing[]=
{
	{ACTION_YOU_HAVE,waiting_other_player, &send_you_have},
	{ACTION_PLAY, waiting_action_ack, &send_play_pck},
	{ACTION_DISCARD, waiting_action_ack, &send_discard_pck},
	{TABLE_END, playing, &do_nothing}
	
};




//Other players turn
STATE waiting_other_player[]=
{
	{RECEIVE_PLAY, waiting_other_player_draw, &manage_play_send_ack	},
	{RECEIVE_YOU_HAVE, playing	, &manage_you_have	}, //Si se llega a perder unos de estos paquetes me parece que se cuelga
	{RECEIVE_DISCARD, waiting_other_player_draw,&manage_discard_send_ack  },
	{LAST_DRAW_SENT, waiting_other_player_last_draw_sent, &do_nothing},
	{TABLE_END, waiting_other_player, &do_nothing}
	
};

//LAST_DRAW_SENT
STATE waiting_action_ack[]=
{
	{RECEIVE_ACK,waiting_other_player,&send_draw_card},
	{TABLE_END, waiting_action_ack, &do_nothing}
	//{TIMEOUT,waiting_action_ack,&resend_action}
};

//MY turn
STATE waiting_other_player_draw[]=
{
	{RECEIVE_DRAW, playing, &remove_card_to_hand},
	{RECEIVE_DRAW_LAST, playing_last_turn_draw_received, &do_nothing},
	{TABLE_END, waiting_other_player_draw, &do_nothing}

};

//*****************************Ending Game STATES **********************************************

	
STATE waiting_other_player_last_draw_sent[]=
{
	{RECEIVE_PLAY, playing_last_turn_draw_sent	, &manage_play_send_ack	},
	{RECEIVE_YOU_HAVE, playing_last_turn_draw_sent	, &manage_you_have	}, //Si se llega a perder unos de estos paquetes me parece que se cuelga
	{RECEIVE_DISCARD, playing_last_turn_draw_sent,&manage_discard_send_ack  },
	{LAST_DRAW_SENT, playing_last_turn_draw_sent, &do_nothing},
	{TABLE_END, waiting_other_player_last_draw_sent, &do_nothing}
	
};


STATE playing_last_turn_draw_sent[]=
{
	{ACTION_YOU_HAVE,waiting_receive_result_draw_sent, &send_you_have},
	{ACTION_PLAY, waiting_receive_result_draw_sent, &send_play_pck},
	{ACTION_DISCARD, waiting_receive_result_draw_sent, &send_discard_pck},
	{TABLE_END, playing_last_turn_draw_sent, &do_nothing}
	
};

STATE waiting_receive_result_draw_sent[]=
{

	{RECEIVE_WE_WON, play_again_quit_menu, &send_you_have},
	{RECEIVE_WE_LOST, play_again_quit_menu, &send_play_pck},
	{RECEIVE_GAME_OVER, play_again_quit_menu, &send_discard_pck},
	{TABLE_END, waiting_receive_result_draw_sent, &do_nothing}
	
};


//Draw received

STATE playing_last_turn_draw_received[]=
{
	{ACTION_YOU_HAVE,waiting_other_player_last_draw_received, &send_you_have},
	{ACTION_PLAY, waiting_other_player_last_draw_received, &send_play_pck},
	{ACTION_DISCARD, waiting_other_player_last_draw_received, &send_discard_pck},
	{TABLE_END, waiting_other_player_last_draw_received, &do_nothing}
	
};

STATE waiting_other_player_last_draw_received[]=
{
	{RECEIVE_PLAY, play_again_quit_menu	, &manage_play_send_ack	},
	{RECEIVE_YOU_HAVE, play_again_quit_menu	, &manage_you_have	}, //Si se llega a perder unos de estos paquetes me parece que se cuelga
	{RECEIVE_DISCARD, play_again_quit_menu,&manage_discard_send_ack  },
	{LAST_DRAW_SENT, play_again_quit_menu, &do_nothing},
	{TABLE_END, waiting_other_player_last_draw_sent, &do_nothing}
	
};


STATE waiting_receive_result_draw_received[]=
{
	{RECEIVE_WE_WON, play_again_quit_menu, &send_you_have},
	{RECEIVE_WE_LOST, play_again_quit_menu, &send_play_pck},
	{RECEIVE_GAME_OVER, play_again_quit_menu, &send_discard_pck},
	{TABLE_END, waiting_receive_result_draw_sent, &do_nothing}
};



STATE play_again_quit_menu[]=
{
	{TABLE_END, play_again_quit_menu, &do_nothing}

};


//
//STATE waiting_draw_ack[]=
//{
//	{RECEIVE_ACK,waiting_other_player,&message_other_player_turn},
//	{TABLE_END, waiting_draw_ack, &do_nothing}
//	//{TIMEOUT,waiting_action_ack,&resend_draw}
//
//	
//};

#endif 
//FIN DE PROTOCOLO DE COMUNICACION  inicio de estados de juego