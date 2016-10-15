/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TFTPServer.cpp
 * Author: r2d2
 * 
 * Created on July 13, 2016, 11:35 PM
 */

#include "TFTPServer.h"
#include <ctime>


TFTPServer::TFTPServer(const char* server_adress, unsigned int port ,unsigned int ip_mode )
{
	temp_server_socket = NULL;
	apr_sockaddr_t *sa; //esta variable vendria a ser la referencia a nuestro "socket" universal. la usamos para dirigirnos al socket.
	apr_socket_t *s;//socket de nuestro server

	if( (cxn_status = apr_sockaddr_info_get(&sa, server_adress,ip_mode, port, 0, mem_pool))==APR_SUCCESS)
	{
		if( (cxn_status = apr_socket_create(&s,APR_UNSPEC, SOCK_STREAM, APR_PROTO_TCP, mem_pool))==APR_SUCCESS)
		{
			//aqui especificamos a mano parametros de nuestro socket
			apr_socket_opt_set(s, APR_SO_NONBLOCK, 1);//aqui definimos que las operaciones son no_bloqueantes
			apr_socket_timeout_set(s, 0);//El 0 va con la condicion de no bloqueante. Hace que el intento de aceptar conexiones sea puntual.
			apr_socket_opt_set(s, APR_SO_REUSEADDR, 1);//si en el futuro matamos la conexion, podemos reusar el socket
			if( (cxn_status = apr_socket_bind(s, sa))==APR_SUCCESS && (cxn_status = apr_socket_listen(s,SOMAXCONN)) ==APR_SUCCESS)
				temp_server_socket = s;
		}
	}
		
}


TFTPServer::~TFTPServer()
{
	if (temp_server_socket!=NULL)
		apr_socket_close(temp_server_socket);
}




TFTPServer::TFTPServer(const TFTPServer& orig) {
	
}





bool TFTPServer::listen_for_client( double timeout_time) //in seconds double (supports miliseconds)
{
	
	clock_t init_time=clock();//nos deja usar miliseg como sabe los pibes(de stackoverflow)
	while( ((clock()-init_time)/(double)CLOCKS_PER_SEC)<timeout_time && socket == NULL)
		apr_socket_accept(&socket, temp_server_socket , mem_pool);

	if(socket)
	{
		apr_socket_opt_set(temp_server_socket, APR_SO_NONBLOCK, 1);//defino la opcion NONBLOCK de la conexion como 1. si hubiera puesto 0, lo hago bloqueante.
		apr_socket_timeout_set(temp_server_socket, DEF_SOCK_TIMEOUT);//defino cuanto tiempo maneja la conexion en sus operaciones antes del timeout
	}

	return socket != NULL; //conection established
	
}