/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "TFTP_Packet.h"
#include "hanabi_game_fsm.h"

unsigned int event_generator (TFTP_Packet* packet)
{
    events_type event_name; 
    
    //I use switch to look all the packets and generate the correct event
    switch ((packet->get_data_pck())[0]){
        
        //Game configuration and communication cases
        case HANABI_ACK_OP:
        {
            event_name = RECEIVE_ACK;
            break;
        }
        
        case HANABI_NAME_OP:
        {
            event_name = RECEIVE_NAME;
            break;
        }
        
        case HANABI_NAME_IS_OP:
        {
            event_name = RECEIVE_NAME_IS;
            break;
        }
        
        case HANABI_START_INFO_OP:
        {
            event_name = RECEIVE_START_INFO;
            break;
        }
            
        //Game start cases
        case HANABI_YOU_START_OP:
        {
            event_name = RECEIVE_USTART;
            break;
        }
        
        case HANABI_ISTART_OP:
        {
            event_name = RECEIVE_ISTART;
            break;
        }
        
        //GamePlay cases
        case HANABI_DISCARD_OP:
        {
            event_name = RECEIVE_DISCARD;
            break;
        }
            
        case HANABI_PLAY_OP:
        {
            event_name = RECEIVE_PLAY;
            break;
        }
        
        case HANABI_YOU_HAVE_OP:
        {
            event_name = RECEIVE_YOU_HAVE;
            break;
        }
        
        case HANABI_DRAW_OP:
        {
            event_name = RECEIVE_DRAW;
            break;
        }
        
#warning ("Warning: los siguientes paquetes no se que eventos generan. Ademas ver la diferencia entre, RECEIVE_USTART, RECEIVE_ISTART y RECEIVE_YOU_HAVE, RECEIVE_DISCARD")
        /*
        //Match End cases
        case HANABI_WE_WON_OP:
        {
            event_name = ;
            break;
        }
            
        case HANABI_WE_LOST_OP:
        {
            event_name = ;
            break;
        }
            
        case HANABI_MATCH_OVER_OP:
        {
            event_name = ;
            break;
        }
        
        //Game finished cases
        case HANABI_PLAY_AGAIN_OP:
        {
            event_name = ;
            break;
        }
        
        case HANABI_GAME_OVER_OP:
        {
            event_name = ;
            break;
        }
            
        //Quit and errir handling
        case HANABI_QUIT_OP:
        {
            event_name = ;
            break;
        }
        */
        case HANABI_ERROR_OP:
        {
            event_name = RECEIVE_ERROR;
            break;
        }
    }
    return event_name; //After searching all the packets, I return the corresponding event
    #warning ("Warning: no se que poner en default")
    
}

