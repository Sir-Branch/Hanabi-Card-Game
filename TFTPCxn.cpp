
#include <time.h>
#include <apr-1.0/apr_general.h>
#include <apr-1.0/apr_network_io.h>
#include <apr-1.0/apr_strings.h>
#include <apr-1.0/apr_file_io.h>
#include "TFTPCxn.h"
#include "TFTP_Packet.h"


TFTPCxn::TFTPCxn()
{
	mem_pool=0;
	apr_pool_create(&mem_pool, NULL);
	socket=0;
	
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
apr_status_t TFTPCxn::send_packet(TFTP_Packet * pck_to_send)
{
	apr_status_t rv;
	unsigned long int len_send = pck_to_send->size();
	
	std::cout << "sending packet length "<<len_send<<std::endl;//Debugging
	
	rv = apr_socket_send(this->socket, pck_to_send->get_data_pck() , &len_send); //simplemente mandamos al socket "sock" el string "req_hdr" del largo len. Es an�logo para cualquier bloque de bytes que queramos mandar.
	if (rv != APR_SUCCESS)
		std::cout << "CANNOT send info\n" ;
	else if(len_send != pck_to_send->size()) // nose si podria pasar 
		std::cout << "Incomplete packet sent(like your birth) D:\n";
	else
		std::cout <<"Packet has been sent \n";
	return rv;
	
}

