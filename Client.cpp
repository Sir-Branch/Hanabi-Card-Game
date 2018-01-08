#include "Client.h"
#include <iostream>
using namespace std;

Client::Client()
{
	if(state == READY)
		cout << "[NET_CONNECTION][INFO] : Client ready." << endl;
}
bool Client::connect_to_server(string server, unsigned int port, unsigned int timeout_ms)
{
	unsigned int start_time = clock();
	unsigned int elapsed_time;
	bool success = false;
	if (state == READY)
	{
		cout << "[NET_CONNECTION][INFO] : Attempting connection to server: ";
		cout << server << ":" << port << ", timeout:" << timeout_ms << "ms." << endl;
		apr_sockaddr_t *sa;
		if (apr_sockaddr_info_get(&sa, server.c_str(), AF_INET, port, 0, mp) == APR_SUCCESS)
		{
			if (apr_socket_create(&sock, APR_UNSPEC, SOCK_STREAM, APR_PROTO_TCP, mp) == APR_SUCCESS)
			{
				bool timed_out = false;
				apr_socket_opt_set(sock, APR_SO_NONBLOCK, 1);
				apr_socket_timeout_set(sock, 0);	//t == 0 – read and write calls never block
				state = CONNECTING;
				while (state == CONNECTING && !(timed_out = (elapsed_time = (unsigned int)(((float)(clock()-start_time)/(float)CLOCKS_PER_SEC)*1000)) >= timeout_ms))
				{
					apr_status_t rv = apr_socket_connect(sock, sa);
					if (rv == APR_SUCCESS)
					{
						state = CONNECTED;
						success = true;
						cout << "[NET_CONNECTION][INFO] : Connected to server!" << endl;
					}
				}
				if (state != CONNECTED)
				{
					apr_socket_close(sock);
					sock = NULL;
					if(timed_out)
						cout << "[NET_CONNECTION][INFO] : Timeout after " << elapsed_time << "ms." << endl;
				}
			}
		}
		if(state != CONNECTED)
			cout << "[NET_CONNECTION][INFO] : Could not connect to server."  << endl;
	}
	else
		cerr << "[NET_CONNECTION][ERROR] : Bad call to connect to server." << endl;
	return success;
}

Client::~Client()
{
	if (state != FATAL_ERROR)
		cout << "[NET_CONNECTION][INFO] : Closing client..." << endl;
}