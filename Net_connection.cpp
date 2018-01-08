#include "Net_connection.h"
#include <iostream>
#include <iterator>
#include <iomanip>

using namespace std;

Net_connection::Net_connection()
{
	cout << "[NET_CONNECTION][INFO] : Creating net connection..." << endl;
	sock = NULL;
	mp = NULL;
	//It is safe to call apr_initialize several times as long as
	//apr_terminate is called the same number of times.

	state = FATAL_ERROR;	//Will change to ready if everything is ok!

	if (apr_initialize() != APR_SUCCESS)	//Initialize Apr. 
		cerr << "[NET_CONNECTION][ERROR] : Could not initialize APR." << endl;

	else if (apr_pool_create(&mp, NULL) != APR_SUCCESS)	//Create pool for net connection
	{
		cerr << "[NET_CONNECTION][ERROR] : Could not create APR pool for net connection." << endl;
		mp = NULL;
		apr_terminate();
	}
	else
		state = READY;
}

bool Net_connection::send_data(const char* data, size_t length, size_t* sent_bytes)
{
	bool success = false;
	size_t bytes = length;
	apr_status_t rv;
	if (sent_bytes != NULL && length != 0)
	{
		if (state == CONNECTED)
		{
			rv = apr_socket_send(sock, data, &bytes);
			*sent_bytes = bytes;
			if (rv == APR_SUCCESS)	//Send data
			{
				ios::fmtflags f(cout.flags());
				cout << "[NET_CONNECTION][INFO] : " << (int) length << " byte(s) sent! Data: " ;
				for (unsigned int i = 0; i < length; i++)
					cout << uppercase << setw(2) << setfill('0') << hex << (int)((unsigned char*)data)[i];
				cout << endl;
				cout.flags(f);
				success = true;
			}
			else
				cerr << "[NET_CONNECTION][ERROR] : Cannot send data." << endl;
		}
		else
			cerr << "[NET_CONNECTION][ERROR] : Attempted to send data, but not connected!" << endl;
	}
	else
		cerr << "[NET_CONNECTION][ERROR] : Bad call to send data." << endl;
	if (!success && state == CONNECTED)
		disconnect();
	return success;
}

bool Net_connection::receive_data(char* data, size_t buffer_size, size_t* received_bytes)
{
	bool success = false;
	apr_status_t rv;
	size_t bytes;
	if (received_bytes != NULL && buffer_size != 0)
	{
		if (state == CONNECTED)
		{
			size_t dummy = 0;
			if (apr_socket_send(sock, data, &dummy) == APR_SUCCESS) //Send 0 bytes to check if connection is OK!
			{
				bytes = buffer_size;
				rv = apr_socket_recv(sock, data, &bytes);
				if (received_bytes != NULL)
					*received_bytes = bytes;
				if (rv == APR_SUCCESS || rv != APR_EOF)
				{
					if (*received_bytes != 0)
					{
						ios::fmtflags f(cout.flags());
						cout << "[NET_CONNECTION][INFO] : Received " << (int)*received_bytes << " byte(s)! Data: ";
						for (unsigned int i = 0; i < *received_bytes; i++)
							cout << uppercase << setw(2) << setfill('0') << hex << (int)((unsigned char*)data)[i];
						cout << endl;
						cout.flags(f);
					}
					success = true;
				}
				else
					cerr << "[NET_CONNECTION][ERROR] : Error receiving data!" << endl;
			}
			if (!success)
				cerr << "[NET_CONNECTION][ERROR] : Error receiving data! Connection with remote computer may have been lost." << endl;
		}
		else
			cerr << "[NET_CONNECTION][ERROR] : Attepted to receive data, but not connected" << endl;
	}
	else
		cerr << "[NET_CONNECTION][ERROR] : Bad call to receive data." << endl;
	if (!success && state == CONNECTED)
		disconnect();
	return success;
}

net_state Net_connection::get_state()
{
	return state;
}

void Net_connection::disconnect()
{
	if (state == CONNECTED)
	{
		state = READY;
		cout << "[NET_CONNECTION][INFO] : Disconnected." << endl;
		apr_socket_close(sock);
		sock = NULL;
	}
}

Net_connection::~Net_connection()
{
	disconnect();
	if (mp != NULL)	//If mp is null (could not create pull) but apr was initialized, apr was terminated in constructor! 
	{
		apr_pool_destroy(mp);
		apr_terminate();
	}
	cout << "[NET_CONNECTION][INFO] : Net connection closed." << endl;
}