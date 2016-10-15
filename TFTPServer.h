/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TFTPServer.h
 * Author: r2d2
 *
 * Created on July 13, 2016, 11:35 PM
 */

#ifndef TFTPSERVER_H
#define TFTPSERVER_H

#include "TFTPCxn.h"

//Server


class TFTPServer: public TFTPCxn
{
public:
    TFTPServer(const char * server_adress = HOME_ADRESS, unsigned int port = DEF_REMOTE_PORT,unsigned int ip_mode = DEF_IPMODE );
    virtual ~TFTPServer();

    bool listen_for_client( double timeout_time); //in seconds double (supports miliseconds)
	
	
protected:
	TFTPServer(const TFTPServer& orig);
	apr_status_t server_stat;//ERROR CONTROL
	apr_socket_t *temp_server_socket; //Server uses SOCKET IN TFTPCxn

};



#endif /* TFTPSERVER_H */

