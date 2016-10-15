
#include <time.h>
#include <apr-1.0/apr_general.h>
#include <apr-1.0/apr_network_io.h>
#include <apr-1.0/apr_strings.h>
#include <apr-1.0/apr_file_io.h>
#include "TFTPCxn.h"


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


