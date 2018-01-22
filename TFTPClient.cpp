/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TFTPClient.cpp
 * Author: r2d2
 * 
 * Created on July 14, 2016, 12:55 AM
 */

#include <time.h>
#include <apr-1.0/apr_general.h>
#include <apr-1.0/apr_network_io.h>
#include <unistd.h>
#include "TFTPClient.h"

TFTPClient::TFTPClient() {
}

TFTPClient::TFTPClient(const TFTPClient& orig) {
}

TFTPClient::~TFTPClient() {
}

apr_status_t TFTPClient::connect_server(const char* server_adress, unsigned int port /*= DEF_REMOTE_PORT*/ ,unsigned int ip_mode /*= DEF_CLIENT_IPMODE*/)//en ipv6
{
	
	apr_sockaddr_t *sa; //esta variable vendria a ser la referencia a nuestro "socket" universal. la usamos para dirigirnos al socket.
	apr_socket_t *mysocket;
	
	if(	(cxn_status = apr_sockaddr_info_get(&sa, server_adress,ip_mode, port, 0, mem_pool))==APR_SUCCESS)
	{
		if( (cxn_status = apr_socket_create(&mysocket,APR_INET, SOCK_STREAM, APR_PROTO_TCP, mem_pool))==APR_SUCCESS)
		{
			//apr_socket_opt_set(mysocket, APR_SO_NONBLOCK, 1);//aqui ACTIVAMOS (PONIENDO 1) la opcion APR_SO_NONBLOCK. Si pusieramos 0 seria bloqueante.
			apr_socket_timeout_set(mysocket, DEF_SOCK_TIMEOUT);//aqui seteamos el tiempo que tarda cualquier operacion (connect, send, reccv, etc) en tirar error si no pasa nada.
			if(	(cxn_status = apr_socket_connect(mysocket, sa))==APR_SUCCESS)
			{
				apr_socket_opt_set(mysocket, APR_SO_NONBLOCK, 1);
				apr_socket_timeout_set(mysocket, DEF_SOCK_TIMEOUT);
				socket=mysocket;
			}
			
		}
	}
	
	return cxn_status;
}

#include "my_sleep_ms.h"
#include <iostream>
#define MS_BETWEEN_CHECKS	50
bool TFTPClient::try_connect_server(double timeout_seconds,const char* server_adress, unsigned int port /*= DEF_REMOTE_PORT*/ ,
											unsigned int ip_mode /*= DEF_CLIENT_IPMODE*/)
{
	apr_status_t status;
	const clock_t begin_time = clock();//Thank you stack overflow <3
	double sleep_time = 0; // Clock freezes while sleeping
	while( (((clock()-begin_time )/(double)CLOCKS_PER_SEC) + sleep_time )<= timeout_seconds
		&& (status = this->connect_server(server_adress,port,ip_mode)) != APR_SUCCESS  )
	{
		my_sleep_ms(MS_BETWEEN_CHECKS);
		sleep_time += (double)MS_BETWEEN_CHECKS/1000.0; //In seconds
	}
	
	return status == APR_SUCCESS; //true successful connection false not able to connect time_out; 
}