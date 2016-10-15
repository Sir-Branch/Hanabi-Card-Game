/* 
 * File:   TFTP_Packet.h
 * Author: gonzalo
 *
 * Created on May 23, 2016, 10:56 AM
 */

#ifndef PACKET_H
#define	PACKET_H

#include <stdlib.h>
#include <apr-1.0/apr_general.h>
#include <apr-1.0/apr_network_io.h>

typedef enum{TFTP_DATA_PCK=1, TFTP_ACK_PCK, TFTP_RQ_PCK, TFTP_ERR_PCK}pck_type_t;
typedef enum{OP_RRQ=1, OP_WRQ, OP_DATA, OP_ACK, OP_ERROR}opcode_t;
typedef enum{NETASCII=9 ,OCTET=6, MAIL=5}rq_mode_t;//aprovechamos y asignamos a cada uno el tamano del string(incluye terminador) MAIL=5 
typedef enum{NOT_DEF, FILE_NOT_FOUND, ACCS_VIOL, DISK_FULL, ILL_TFTP, UNKNOWN_ID, FILE_IN_USE, NO_SUCH_USER}errors_tftp_t;

#define DEFAULT_RQ_MODE                         NETASCII

#define SIZE_OPCODE				2
#define	SIZE_ERRCODE                            2
#define SIZE_BLOCK_NUM                          2
#define TERM_SIZE				1
#define MAX_PACKET_SIZE                         1024
#define MAX_FILE_NAME_LENGTH                    256
#define DATA_SIZE				512

class TFTP_Packet {
	
public:
		
    TFTP_Packet(long unsigned int); //rule of zero/3/5
    TFTP_Packet(const TFTP_Packet& other);
    TFTP_Packet();
    ~TFTP_Packet();
	
    //Funciones de paquetes recibir y enviar los mismo mediante un socket
    apr_status_t send_packet(apr_socket_t *sock); 
    bool recieve_pck(apr_socket_t *sock);
    void print_packet(void);

protected:
    long unsigned int size_pck;
    char *packet_data;
    pck_type_t tftp_packet_type;//RFC 1350 standard
};



#endif	/* PACKET_H */

