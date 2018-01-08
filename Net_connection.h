#ifndef NET_CONNECTION_H_
#define NET_CONNECTION_H_

#define APR_DECLARE_STATIC

#include <apr_pools.h>
#include <apr_general.h>
#include <apr_network_io.h>
#include <iostream>

using namespace std;

typedef enum {READY,CONNECTING,CONNECTED,FATAL_ERROR} net_state;

class Net_connection
{
public:
	Net_connection();
	bool send_data(const char* data, size_t length, size_t* sent_bytes);
	bool receive_data(char* data, size_t buffer_size, size_t* received_bytes);
	net_state get_state();
	void disconnect();
	virtual ~Net_connection();
	//learned something here: http://stackoverflow.com/questions/12092933/calling-virtual-function-from-destructor
	//The actual type of the object changes during construction and it changes again during destruction.
	//When a destructor is being executed, the object is of exactly that type,
	//and never a type derived from it. 
	//Therefore, cannot call virtual function from destructor! must use virtual destructor.
protected:
	apr_pool_t		*mp;		//pool used in class
	apr_socket_t	*sock;		//Remote computer related socket
	net_state state;			//Net connection state
};

//Include other headers so that only #include Net_connection.h is needed
#include "Client.h"
#include "Server.h"
#endif //NET_CONNECTION_H_
