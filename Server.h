#ifndef SERVER_H_
#define SERVER_H_

#include "Net_connection.h"

class Server : public Net_connection
{
public:
	Server(unsigned int port);
	bool listen_for_connection(unsigned int timeout_ms);
	virtual ~Server();
private:
	unsigned int port;
};

#endif //SERVER_H_