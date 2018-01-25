#include "Networking.h"

#define DEF_SOCK_TIMEOUT (APR_USEC_PER_SEC * 5) //TIMEOUT (ver m�s adelante).


Networking::Networking()
{
	apr_initialize();
	apr_pool_create(&memoryPool, NULL);
	auxiliarSocket = NULL;
	principalSocket = NULL;
}

bool Networking::prepareToConnect(std::string ip)
{
	bool retVal = false;
	apr_status_t rv;
	apr_pool_create(&memoryPool, NULL);
	rv = apr_sockaddr_info_get(&socketAddres, ip.c_str() , APR_INET, STANDARD_PORT, 0, memoryPool);
	if (rv == APR_SUCCESS)
	{
		rv = apr_socket_create(&principalSocket, APR_INET, SOCK_STREAM, APR_PROTO_TCP, memoryPool); //cambiar UNSPEC por APR_INET
		if (rv == APR_SUCCESS)
		{
			apr_socket_opt_set(principalSocket, APR_SO_NONBLOCK, 1);
			apr_socket_timeout_set(principalSocket, DEF_SOCK_TIMEOUT);
			retVal = true;
			
		}
		else
			printf("\nCANNOT CREATE SOCKET TO CONNECT");
	}
	else
		printf("\nCANNOT GET SERVER INFO\n");
	return retVal;
}
bool Networking::tryToConnect()
{
	bool retVal=false;
	apr_status_t rv;
	rv = apr_socket_connect(principalSocket, socketAddres);
	if (rv == APR_SUCCESS)
	{
		apr_socket_opt_set(principalSocket, APR_SO_NONBLOCK, 1);
		apr_socket_timeout_set(principalSocket, 0);
		retVal = true;
	}
	return retVal;
}
void Networking::abortConnecting()
{
	if(principalSocket != NULL)
	{
		apr_socket_shutdown(principalSocket, APR_SHUTDOWN_READWRITE);
		apr_socket_close(principalSocket);
	}
	principalSocket = NULL;
}


bool Networking::prepareToListen()
{
	bool retVal = false;
	apr_status_t rv;
	apr_socket_t *news;
	rv = apr_sockaddr_info_get(&socketAddres, NULL, APR_INET, STANDARD_PORT, 0, memoryPool);
	if (rv == APR_SUCCESS)
	{
		rv = apr_socket_create(&news, APR_INET, SOCK_STREAM, APR_PROTO_TCP, memoryPool);
		if (rv == APR_SUCCESS)
		{
			apr_socket_opt_set(news, APR_SO_NONBLOCK, 1);
			apr_socket_timeout_set(news, 0);
			apr_socket_opt_set(news, APR_SO_REUSEADDR, 1);
			rv = apr_socket_bind(news, socketAddres);
			if (rv == APR_SUCCESS)
			{
				rv = apr_socket_listen(news, SOMAXCONN);
				if (rv == APR_SUCCESS)
				{
					auxiliarSocket = news;
					retVal = true;
				}
				else
					printf("\nNOT LISTENING");
			}
			else
				printf("\nfailed to bind socket");

		}
		else
			printf("\ncannot create socket");

	}
	else
		printf("\ncannot get info?");

	return retVal;
}
bool Networking::listen()
{
	bool retVal=false;
	apr_socket_accept(&principalSocket, auxiliarSocket, memoryPool);
	if (principalSocket != NULL)
	{
		apr_socket_shutdown(auxiliarSocket, APR_SHUTDOWN_READWRITE);
		apr_socket_opt_set(principalSocket, APR_SO_NONBLOCK, 1);
		apr_socket_timeout_set(principalSocket, 0);
		retVal = true;
	}
	return retVal;
}

bool Networking::listen_for_client(double timeout_time)
{
	this->prepareToListen();
	bool connected = false;
	clock_t init_time=clock();//nos deja usar miliseg como sabe los pibes(de stackoverflow)
	while( ((clock()-init_time)/(double)CLOCKS_PER_SEC)<timeout_time && !(connected = this->listen()) )
		;
	if(!connected)
		this->abortConnecting();
	
	return connected; //conection established
	
}
#include "TFTP_Packet.h"

bool Networking::send_packet(TFTP_Packet * pck_to_send)
{
	bool retVal = false;
	apr_size_t totalSize = pck_to_send->size();
	apr_status_t rv;
	rv = apr_socket_send(principalSocket, pck_to_send->get_data_pck(), &totalSize);
	if (rv == APR_SUCCESS)
	{
		retVal = true;
		std::cout <<"Packet has been sent \n";
		pck_to_send->print_packet();
	}	
	return retVal;
}
bool Networking::receive_packet(TFTP_Packet ** pck_to_receive)
{
	//unsigned int length;
	apr_size_t totalSize = BUFSIZE;
	bool retVal = false;
	char auxBuffer[BUFSIZE];
	apr_status_t rv;
	rv = apr_socket_recv(principalSocket,(char *) auxBuffer, &totalSize);	//Recieves the paquet and saves the length recieved.
	if (APR_STATUS_IS_EOF(rv) || (totalSize == 0))
		retVal = false;
	else
	{
		*pck_to_receive = new TFTP_Packet( totalSize, auxBuffer);
		std::cout << "Pck Received \n";
		(*pck_to_receive)->print_packet();
		retVal = true;
	}
	return retVal;
}



Networking::~Networking()
{
	apr_socket_shutdown(principalSocket, APR_SHUTDOWN_READWRITE);
	apr_socket_close(principalSocket);
	apr_terminate();
}

#include "my_sleep_ms.h"
#define SLEEP_BETWEEN_CHECK  50.0

bool Networking::try_connect_server(double timeout_seconds, std::string ip)//,std::string &server_adress, unsigned int port /*= DEF_REMOTE_PORT*/ ,unsigned int ip_mode /*= DEF_CLIENT_IPMODE*/)
{
	this->prepareToConnect(ip);
	bool connected = false;
	const clock_t begin_time = clock();//Thank you stack overflow <3
	double sleep_time = 0; // Clock freezes while sleeping
	while( (((clock()-begin_time )/(double)CLOCKS_PER_SEC) + sleep_time )<= timeout_seconds
		&& !(connected = this->tryToConnect()) )
	{
		my_sleep_ms(SLEEP_BETWEEN_CHECK);
		sleep_time += SLEEP_BETWEEN_CHECK/1000.0; //In seconds
	}
	if(!connected)
		this->abortConnecting();
	return connected;
}

bool Networking::connection_status_ok(void)
{
	size_t empty_test = 0;
	char buffer[20];
	return apr_socket_send( principalSocket, buffer, &empty_test) == APR_SUCCESS;

}