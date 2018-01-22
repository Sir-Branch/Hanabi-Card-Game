
#include <time.h>
#include <apr-1.0/apr_general.h>
#include <apr-1.0/apr_network_io.h>
#include <apr-1.0/apr_strings.h>
#include <apr-1.0/apr_file_io.h>
#include "TFTPCxn.h"
#include "TFTP_Packet.h"


TFTPCxn::TFTPCxn()
{
	mem_pool = NULL;
	apr_pool_create(&mem_pool, NULL);
	socket = NULL;
	
}

TFTPCxn::~TFTPCxn()
{
	if(socket!=NULL)
		apr_socket_close(socket);
	apr_pool_destroy(mem_pool);
	 
}


//SOCKET IS READ ONLY ain't want those commies touching our sockets...
apr_socket_t * TFTPCxn::get_cxn_socket()
{
	return socket;
}

#include <iostream>

//apr_status_t TFTPCxn::send_packet(const char * const pck_to_send, unsigned long int size_pck)
bool TFTPCxn::send_packet(TFTP_Packet * pck_to_send)
{
	bool sent = false;
	unsigned long int len_send = pck_to_send->size();
	
	if( this->connection_status_ok())
	{
		std::cout << "sending packet length "<<len_send<<std::endl;//Debugging

		this->cxn_status = apr_socket_send(this->socket, pck_to_send->get_data_pck() , &len_send); //simplemente mandamos al socket "sock" el string "req_hdr" del largo len. Es an�logo para cualquier bloque de bytes que queramos mandar.

		if (this->cxn_status != APR_SUCCESS)
			std::cout << "CANNOT send info\n" ;
		else if(len_send != pck_to_send->size()) // nose si podria pasar 
			std::cout << "Incomplete packet sent(like your birth) D:\n";
		else
		{
			std::cout <<"Packet has been sent \n";
			pck_to_send->print_packet();
			sent = true;
		}
	}
	else
	{
		std::cout << "Connection is not OK!!\n"; 
	}
		
	return sent;
}

#define TFTPCXN_MAX_PCK_SIZE 256 
#warning "Change to 256 max pck size"
bool TFTPCxn::receive_packet(TFTP_Packet ** pck_to_receive)
{
	bool received_packet = false;
	char buffer[TFTPCXN_MAX_PCK_SIZE];
	size_t max_bytes_receive = TFTPCXN_MAX_PCK_SIZE;
	TFTP_Packet * received = NULL;
	if( this->connection_status_ok())
	{
		this->cxn_status = apr_socket_recv(this->socket, buffer, &max_bytes_receive);
		if( (this->cxn_status == APR_SUCCESS || this->cxn_status != APR_EOF) && max_bytes_receive != 0)
		{
			received_packet = true;
			*pck_to_receive = new TFTP_Packet( max_bytes_receive, buffer);
		}
	}
	else
	{
		std::cout << "Connection is not OK!!\n"; 
	}
	return received_packet;
  
}




bool TFTPCxn::connection_status_ok(void)
{
	size_t empty_test = 0;
	char buffer[20];
	return (this->cxn_status = apr_socket_send( this->socket, buffer, &empty_test)) == APR_SUCCESS;
}
 