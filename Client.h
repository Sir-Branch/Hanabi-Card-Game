#ifndef CLIENT_H_
#define CLIENT_H_

#include "Net_connection.h"
#include <string>

using namespace std;

class Client : public Net_connection
{
public:
	Client();
	bool connect_to_server(string server, unsigned int port, unsigned int timeout_ms);
	virtual ~Client();
};

#endif //CLIENT_H_