/* 
 * File:   TFTP_Packet.cpp
 * Author: gonzalo
 * 
 * Created on May 23, 2016, 10:56 AM
 */


#include <iostream>
#include <string>

#include <strings.h>
#include <apr-1.0/apr_general.h>
#include <apr-1.0/apr_network_io.h>

#include "TFTP_Packet.h"
#include "Hanabi_Ack_Packet.h"

//using namespace std;

TFTP_Packet::TFTP_Packet(long unsigned int size, const char * data) : size_pck(size) {
	packet_data = new char [size];
	if(data != NULL && size)
		memcpy(packet_data, data, size);
}

TFTP_Packet::~TFTP_Packet() {
    delete[] packet_data;
}

TFTP_Packet::TFTP_Packet(const TFTP_Packet& other)
{
	size_pck = other.size_pck;
	packet_data = new char[size_pck];
	if(packet_data != NULL)
	{
		memcpy(packet_data,other.packet_data,size_pck);
		tftp_packet_type = other.tftp_packet_type;
	}
}
    
TFTP_Packet::TFTP_Packet()
{
	size_pck = 0;
	packet_data=NULL;//NULL pero en c++ se usa 0 pq son ezzzpeciales 
}




/*
 * Envia un paquete usando apr al socket dado, devuelve apr_status_t
 * 
 * Input:
 *		apr_socket_t *sock: puntero al socket de red al que se quiera mandar el paquete
 * 
 * Return Value:
 *		apr_status_t de poder enviar correcta devuele APR_SUCCESS de lo contrario algun tipo de error de APR
 * 
 * 
 */
apr_status_t TFTP_Packet::send_packet(apr_socket_t *sock)
{
	apr_status_t rv;
	unsigned long int len_send=size_pck;
	std::cout << "sending packet length "<<size_pck<<std::endl;
	rv = apr_socket_send(sock, packet_data, &len_send); //simplemente mandamos al socket "sock" el string "req_hdr" del largo len. Es an�logo para cualquier bloque de bytes que queramos mandar.
	if (rv != APR_SUCCESS)
		std::cout << "CANNOT send info\n" ;
	else if(len_send!=size_pck) // nose si podria pasar 
		std::cout << "Incomplete packet sent(like your birth) :D\n";
	else
		std::cout <<"Packet has been sent"<<std::endl;
	return rv;
	
}

/*
 * Envia un paquete usando apr al socket dado, devuelve apr_status_t
 * 
 * Input:
 *		apr_socket_t *sock: puntero al socket de donde se quiera levantar el paquete
 * 
 * Return Value:
 *		bool: true(1) si recibio un paquete. False(0) sino recibio o se produjo un error(ej; allocacion de memoria)
 * 
 * 
 */
/*
bool TFTP_Packet::recieve_pck(apr_socket_t *sock)
{
	bool packet_picked_up=false;
	char buf[MAX_PACKET_SIZE+1];
	long unsigned int len_to_pickup=MAX_PACKET_SIZE+1;
	apr_status_t rv = apr_socket_recv(sock, buf, &len_to_pickup);//levanto el buffer de red.
	if(rv==APR_SUCCESS && len_to_pickup > 0 && len_to_pickup<=MAX_PACKET_SIZE )
	{
		if(packet_data!=NULL)//evitamos memoryleaks como unos champions
			delete[] packet_data;
		size_pck=len_to_pickup;
		packet_data= new char[size_pck];
		if(packet_data!=NULL)
		{
			memcpy(packet_data,buf,size_pck);
			packet_picked_up=true;
			std::cout<<"Packet recieved"<<std::endl;
		}
	}
	//else
	//	std::cout<<"No packet recieved"<<std::endl;e
	

	return packet_picked_up;
	
}*/

#include <stdio.h>
void TFTP_Packet::print_packet(void)
{
	if(size_pck)
	{	
		std::cout<< "0x"; 
		for(int i = 0 ; i < size_pck ; i++)
			printf("%X ",(unsigned char)packet_data[i]);
		
		printf("\n");
	}	
}


const char *  TFTP_Packet::get_data_pck(void)
{
	return (const char *) this->packet_data; //Read Only. LOOKY BUT NO TOUCHY, cunt.
}


long unsigned int TFTP_Packet::size(void)
{
	return this->size_pck;
}