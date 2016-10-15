/* 
 * File:   TFTPClient.h
 * Author: r2d2
 *
 * Created on July 14, 2016, 12:55 AM
 */

#ifndef TFTPCLIENT_H
#define TFTPCLIENT_H

//Client


#include <apr-1.0/apr_general.h>
#include <apr-1.0/apr_network_io.h>

#include "TFTPCxn.h"

class TFTPClient : public TFTPCxn{
public:
    
    TFTPClient();
    TFTPClient(const TFTPClient& orig);
    virtual ~TFTPClient();
	
    apr_status_t connect_server(const char* server_adress, unsigned int port /*= DEF_REMOTE_PORT*/ ,unsigned int ip_mode /*= DEF_IPMODE*/);
    bool try_connect_server(double time_seconds,const char* server_adress, unsigned int port /*= DEF_REMOTE_PORT*/ ,
											unsigned int ip_mode /*= DEF_IPMODE*/);
};





#endif /* TFTPCLIENT_H */

