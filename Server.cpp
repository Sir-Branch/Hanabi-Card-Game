#include "Server.h"
#include <iostream>

Server::Server(unsigned int port)
{
	this->port = port;
	if(state == READY)
		cout << "[NET_CONNECTION][INFO] : Server ready, port " <<  port << "." << endl;
}

bool Server::listen_for_connection(unsigned int timeout_ms)
{
	bool success = false;
	apr_socket_t* serv_sock = NULL;
	if (state == READY)
	{
		apr_sockaddr_t* sa;
		if (apr_sockaddr_info_get(&sa, NULL, AF_INET, port, 0, mp) == APR_SUCCESS)
		{
			if (apr_socket_create(&serv_sock, APR_UNSPEC, SOCK_STREAM, APR_PROTO_TCP, mp) == APR_SUCCESS)	//Create socket
			{
				apr_socket_opt_set(serv_sock, APR_SO_NONBLOCK, 1);
				apr_socket_timeout_set(serv_sock, 0);	//t == 0 � read and write calls never block /
				if (apr_socket_bind(serv_sock, sa) == APR_SUCCESS)	//Bind!
				{
					//Now, listen for connections!
					if (apr_socket_listen(serv_sock, SOMAXCONN) == APR_SUCCESS)
					{
						bool timed_out = false;
						unsigned int start_time = clock();
						unsigned int elapsed_time;
						cout << "[NET_CONNECTION][INFO] : Listening for connections, timeout: ";
						cout << timeout_ms << "ms." << endl;
						clock_t server_timer = clock();
						state = CONNECTING;
						//Wait for clients
						do
							apr_socket_accept(&sock, serv_sock, mp);
						while 
							(
							//Not connected
							sock == NULL &&					
							//State is connecting
							state == CONNECTING &&			
							//And we didn't timeout
							!(timed_out = (elapsed_time = (unsigned int)(((float)(clock() - start_time) / (float)CLOCKS_PER_SEC) * 1000)) >= timeout_ms)
							);
						//If this is true then we are connected!
						if (sock != NULL)
						{
							apr_socket_opt_set(sock, APR_SO_NONBLOCK, 1);
							apr_socket_timeout_set(sock, 0);
							state = CONNECTED;
							cout << "[NET_CONNECTION][INFO] : Connected to client!" << endl;
							success = true;
						}
						else if(timed_out)
							cout << "[NET_CONNECTION][INFO] : Timeout after " << elapsed_time << "ms." << endl;
					}
				}
			}
		}
		if(state != CONNECTED)
			cout << "[NET_CONNECTION][INFO] : No client connected." << endl;
	}
	else
		cerr << "[NET_CONNECTION][ERROR] : Bad call to listen for connection." << endl;
	if (serv_sock != NULL)
	{
		//Always close this, since we won't use it.
		apr_socket_close(serv_sock);
		serv_sock = NULL;
	}
	return success;
}

Server::~Server()
{
	if (state != FATAL_ERROR)
		cout << "[NET_CONNECTION][INFO] : Closing server..." << endl;
}