
#if 0
#include "hanabi_game_fsm_callbacks.h"

typedef void (*action_t) (hanabi_game_data_t *user_data); 

typedef struct state_table
{
	event_t  event;
	struct state_table *prx_estado;
	action_t action;
	
}STATE;
	
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
extern STATE waiting_draw_ack[];

	
STATE main_menu[]=
{													
	{PLAY_CLICKED, connection_menu,&do_nothing},
    {SETTINGS_CLICK, settings_menu,&do_nothing}, //change resolution music, etc
  
};

STATE connection_menu[]=
{
	{JOIN_CLICKED, searching_for_game,&do_nothing},
	{HOST_CLICKED, waiting_for_client,&do_nothing}
	
};


STATE settings_menu[]=
{
	{APPLY_CLICKED, main_menu,&do_nothing},
	{CANCEL_CLICKED, main_menu,&do_nothing}

};

//****************************************CONNECTION START****************************************************

STATE searching_for_game[]=
{
	
	{TIMEOUT,waiting_for_client,&},
	{FOUND_SERVER,connected_to_server,&}
};

//****************************************SERVER STATES****************************************************

STATE waiting_for_client[]=
{
	{CLIENT_CONNECTED, asking_client_name, &send_name_pck},
	
};


STATE asking_client_name[]=
{
	{RECEIVE_NAME_IS,ack_client_name_is,&send_ack_pck},
	//{TIMEOUT,asking_client_name,&send_name_pck},
	
	
};

STATE ack_client_name_is[]=
{
	{RECEIVE_NAME , sending_server_name_is, &send_name_is_pck},
//	{TIMEOUT, ack_client_name_is, &send_ack_pck}
};

STATE sending_server_name_is[]=
{
	{RECEIVE_ACK , sending_start_info_client,&start_game_send_start_info_pck},
	//{TIMEOUT, sending_server_name_is, &send_name_is_pck}

};

STATE sending_start_info_client[]=
{
	{RECEIVE_ACK, defining_start_player, &create_send_random_start},//Will send YOU_START or I_START 
	{RECEIVE_ERROR, manage_error_pck, &do_nothing},
	
	//{TIMEOUT, sending_server_name_is, &send_start_info_pck}

	
};

//Primera jugada del partido es un estado que solo ocurrira una vez
STATE defining_start_player[]=//SERVER
{
	{RECEIVE_ACK, playing	, &do_nothing}, // Fue mandado un I start
	
	//Fue mandado un U_START
	{RECEIVE_PLAY, waiting_other_player_draw, &manage_play_send_ack	},
	{RECEIVE_YOU_HAVE, playing	, &manage_you_have_send_ack	}, //Si se llega a perder unos de estos paquetes me parece que se cuelga
	{RECEIVE_DISCARD, waiting_other_player_draw,&manage_discard_send_ack  },
	
	//{TIMEOUT,defining_start_player, &resend_random_start}
	
};


STATE waiting_starting_player[]=//CLIENT
{
	{RECEIVE_USTART,playing ,&do_nothing},
	{RECEIVE_ISTART,waiting_other_player,&send_ack_pck},
		
};


// ************************ CLIENT STATES ********************************
STATE connected_to_server[]=
{
	{RECEIVE_NAME, sending_name_to_server,&send_name_is_pck},
	
	

};

STATE sending_name_to_server[]=
{
	{RECEIVE_ACK, waiting_name_server ,&send_name_pck},
	//{TIMEOUT, sending_name_to_server ,&send_name_is_pck}
	
	

};

STATE waiting_name_server[]=
{
	{RECEIVE_NAME_IS, waiting_start_info,&send_ack_pck},
//	{TIMEOUT, waiting_name_server ,&send_name_pck}

	

};

STATE waiting_start_info[]=
{
	//{RECEIVE_START_INFO, validating_start_info ,&manage_receive_start_info}, //Will generate an Error event or ack 
	{RECEIVE_START_INFO, waiting_starting_player ,&manage_receive_start_info}, //Will generate an Error event or ack 

};

STATE validating_start_info[]=
{
	{START_INFO_OK, waiting_starting_player, &send_ack_pck},
	{START_INFO_ERROR, manage_error ,&send_error}, //generated events

};

STATE waiting_starting_player[]=
{
	{RECEIVE_YOU_START, playing ,&do_nothing},
	{RECEIVE_I_START, waiting_other_player,&send_ack_pck}

};


//*****************************GAME STATES NO CLIENT OR SERVER**********************************************


STATE playing[]=
{
	{ACTION_YOU_HAVE,waiting_other_player, &send_you_have},
	{ACTION_PLAY, waiting_action_ack, &send_play_pck},
	{ACTION_DISCARD, waiting_action_ack, &send_discard_pck},
	
};



//MY turn
STATE waiting_other_player_draw[]=
{
	{RECEIVE_DRAW, playing, &remove_card},

	//Se perdio el ack si llega una de estas 
	//{RECEIVE_PLAY, waiting_other_player_draw	, &send_ack_pck	},
	//{RECEIVE_DISCARD, waiting_other_player_draw,&send_ack_pck  },

};

//Other players turn
STATE waiting_other_player[]=
{
	{RECEIVE_PLAY, waiting_other_player_draw	, &manage_play_send_ack	},
	{RECEIVE_YOU_HAVE, playing	, &manage_you_have_send_ack	}, //Si se llega a perder unos de estos paquetes me parece que se cuelga
	{RECEIVE_DISCARD, waiting_other_player_draw,&manage_discard_send_ack  },
	
};


STATE waiting_action_ack[]=
{
	{RECEIVE_ACK,waiting_draw_ack,&send_draw_card},
	//{TIMEOUT,waiting_action_ack,&resend_action}
	
	
};

STATE waiting_draw_ack[]=
{
	{RECEIVE_ACK,waiting_other_player,&do_nothing},
	//{TIMEOUT,waiting_action_ack,&resend_draw}

	
};

#endif 
//FIN DE PROTOCOLO DE COMUNICACION  inicio de estados de juego