#ifndef PORT_FUNCTIONS_H
#define PORT_FUNCTIONS_H 


#define ACCA (accumulatord.split.acca) 
#define ACCB (accumulatord.split.accb) 
#define ACCD (accumulatord.whole.accd) 
#define ACCD_ADR &(accumulatord.whole) //MUST USE THIS CANNOT USE &ACCD 


#define SIZE_ACCD 16 //16bits
#define SIZE_ACCAB 8 //8bits
#define NUM_BITS 8

#define SUCCESS 0

#pragma pack(push,1) //Set alignment to 1, else the size of accumulator will be 4BYTES WE DO NOT WANT THAT

typedef unsigned char BYTE;
typedef struct { BYTE accb,acca; }registry_t;

typedef struct 
{
	
	union{
		unsigned int accd	:SIZE_ACCD; 
		struct{
			  unsigned int bit0		:1; //During program execution, we dont work with bitfield directly. 
			  unsigned int bit1		:1;	//So it might result rather oblivious to declarate the port in this way.
			  unsigned int bit2		:1;// But it allows us to access specific bits if needed
			  unsigned int bit3		:1;
			  unsigned int bit4		:1;
			  unsigned int bit5		:1;
			  unsigned int bit6		:1;
			  unsigned int bit7		:1;
			  unsigned int bit8		:1;
			  unsigned int bit9		:1;
			  unsigned int bit10	:1;
			  unsigned int bit11	:1;
			  unsigned int bit12	:1;
			  unsigned int bit13	:1;
			  unsigned int bit14	:1;
			  unsigned int bit15	:1;
			};
		};

}whole_reg;

union accumulator{

	whole_reg whole;
	registry_t split;

};
#pragma pack(pop)



int bitset(void *accumulator,unsigned int bytes_of_accumulator, unsigned int bit_to_set);
int bitclr(void *accumulator,unsigned int bytes_of_accumulator, unsigned int bit_to_set);
int bitToggle(void *accumulator,unsigned int bytes_of_accumulator, unsigned int bit_to_set);
int getbit(void *accumulator,unsigned int bytes_of_accumulator, unsigned int bit_to_set);
int maskmanage(void *accumulator,unsigned int bytes_accum,char *mask,
				int (*what2do)(void *accumu,unsigned int bytes_accum, unsigned int bit2set) );

void print_ports(unsigned int port_content,unsigned int counter);


#endif