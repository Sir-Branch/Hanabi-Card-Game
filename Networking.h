#ifndef NETWORKING_H
#define NETWORKING_H

#include <iostream>
#include <string>
#include <apr_general.h>
#include <apr_file_io.h>
#include <apr_strings.h>
#include <apr_network_io.h>
#include "TFTP_Packet.h"

#define BUFSIZE	516 
#define HEADER_SIZE 1
#define STANDARD_PORT 13796 	
#define HOME_IP "127.0.0.1"

class Networking
{
public:
	Networking();
	bool send_packet(TFTP_Packet * pck_to_send);
	bool receive_packet(TFTP_Packet ** pck_to_receive);	
	bool try_connect_server(double timeout_seconds,std::string ip);//,std::string &server_adress, unsigned int port /*= DEF_REMOTE_PORT*/ ,unsigned int ip_mode /*= DEF_CLIENT_IPMODE*/)
	bool listen_for_client(double timeout_time);
	bool connection_status_ok(void);
	
	~Networking();
protected:
	
	bool prepareToConnect(std::string ip);
	bool tryToConnect();
	void abortConnecting();
	bool prepareToListen();
	bool listen();
	
	apr_pool_t *memoryPool;
	apr_socket_t *auxiliarSocket;
	apr_socket_t *principalSocket;
	apr_sockaddr_t *socketAddres;
};



#endif 