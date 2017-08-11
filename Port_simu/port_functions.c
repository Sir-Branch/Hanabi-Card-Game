#include <stdio.h>
#include <string.h>
#include "port_functions.h"



static int validate_mask(int strlen,char *mask);
static int validate_input(unsigned int bytes_of_accumulator, int bit_to_set);
static long unsigned int space_counter(char *mask);

/*ALL THESE PROGRAMS RECEIVE THE POINTER TO THE ACCUMULATOR IN VOID
  ,BYTES OF THE ACCUMULATOR, AND WHICH BIT TO MODIFY.
*/

int bitset(void *accumulator,unsigned int bytes_of_accumulator, unsigned int bit_to_set)
{
	int error_status=SUCCESS;
	if(validate_input(bytes_of_accumulator,bit_to_set))//SUCCESS 0, WILL NOT ENTER
		error_status=EOF;
	else
	{
		accumulator=(char*)accumulator+bit_to_set/NUM_BITS;//BIT TO MODIFY COULD HAVE DONE IN THE SAME LONG BUT 
		*(char*)accumulator|=1<<(bit_to_set%NUM_BITS);//Calculate the 
	}
	return error_status;

}


int bitclr(void *accumulator,unsigned int bytes_of_accumulator, unsigned int bit_to_set)//Allows us to work with more than 1 byte accumulators 
{
	int error_status=SUCCESS;
	if(validate_input(bytes_of_accumulator,bit_to_set))//SUCCESS 0, WILL NOT ENTER
		error_status=EOF;
	else 
	{
		accumulator=(char*)accumulator+bit_to_set/NUM_BITS;//BIT TO MODIFY
		*(char*)accumulator&=(0xFF&0<<(bit_to_set%NUM_BITS));
	}
	return error_status;

}

int bitToggle(void *accumulator,unsigned int bytes_of_accumulator, unsigned int bit_to_set)
{
	int error_status=SUCCESS;
	if(validate_input(bytes_of_accumulator,bit_to_set))//SUCCESS 0, WILL NOT ENTER
		error_status=EOF;
	else
	{
		accumulator=(char*)accumulator+bit_to_set/NUM_BITS;//BIT TO MODIFY
		*(char*)accumulator^=1<<(bit_to_set%NUM_BITS);
	}
	return error_status;

}


int getbit(void *accumulator,unsigned int bytes_of_accumulator, unsigned int bit_to_set)
{
	int result;
	if(validate_input(bytes_of_accumulator,bit_to_set))//SUCCESS 0, WILL NOT ENTER
		result=EOF;
	else
	{
		
		result=*((char*)accumulator+bit_to_set/NUM_BITS);
		result&=1<<(bit_to_set%NUM_BITS);
		if(result>0)//If its bigger than 0 than the bit is on
			result=1; //else it would be 0 so no need for return_value=0
	}
	return result;

}


/*
	Mask manage example: CAN TAKES SPACES ANYWHERE
	
	ACCD: 0000 0000 0000 0000
	maskmanage(ACCD_ADR,2,"1111100000100110",&bitset);
	ACCD: 1111 1000 0010 0110
	maskmanage(&ACCA,1,"0001 0111",&bitToggle);
	ACCD: 1110 1111 0010 0110
	maskmanage(&ACCB,1,"     11",&bitclear);
	ACCD: 1110 1111 0010 0100
	
*/
int maskmanage(void *accumulator,unsigned int bytes_accum,char *mask,
				int (*what2do)(void *accumu,unsigned int bytes_accum, unsigned int bit2set) )
{
	int i, error_status=SUCCESS;
	unsigned long int string_len=strlen(mask), total_spaces=space_counter(mask),space_count;
	
	if( (string_len-total_spaces)>bytes_accum*NUM_BITS)
		//We compare strlen minus the space count with the total size in bits of the accumulator
		error_status=EOF;
	else
		error_status=validate_mask(string_len,mask);
	
	if(error_status==SUCCESS)
		for(i=0,space_count=0;i<string_len;i++)
			switch(mask[i])
			{
				case '1':
					what2do((void *)accumulator,bytes_accum,string_len-((i-space_count)+1+total_spaces));//run the pointer to function passed
					break;
				case ' ':
					//rintf("space in i=%d\n count is %lu",i,space_count);
					space_count++;
					break;//DO NOTHING
				default:
					break; //IF THE PROGRAM REACHED THIS STAGE SOMETHING WENT WRONG. sHOULD WE EXIT??
			}
	return error_status;
}

/* NO SPACE DETECT
int maskmanage(void *accumulator,unsigned int bytes_accum,char *mask,
				int (*what2do)(void *accumu,unsigned int bytes_accum, unsigned int bit2set) )
{
	int i,error_status=SUCCESS;
	unsigned long int string_len;

	if((string_len=strlen(mask))>bytes_accum*NUM_BITS)
		error_status=EOF;
	else
		error_status=validate_mask(string_len,mask);
	if(error_status==SUCCESS)
		for(i=0;i<string_len;i++)
			switch(mask[i])
			{
				case '1':
					what2do((void *)accumulator,bytes_accum,string_len-(i+1));//run the pointer to function passed
					break;
				default:
					break;//DO NOTHING
			}
}*/


long unsigned int space_counter(char *mask)
{
	long unsigned int counter=0;
	int i;
		for(i=0;;i++)
			if(mask[i]==' ')
			{
				counter++;
				continue;
			}
			else if(mask[i]==0)
				break;
			else
				continue;
	return counter;
	
}



int validate_mask(int strlen,char *mask) //FUNCTION validates that the mask only contains binary input 
{
	int i,error_status=SUCCESS;
	for(i=0;i<strlen;i++)
		if(mask[i]=='0' || mask[i]=='1' || mask[i]==' ' )//validates each element of the mask string
			continue;
		else
		{
			//printf("not valid\n");
			error_status=EOF;
			break;
		}
	return error_status;

}


int validate_input(unsigned int bytes_of_accumulator, int bit_to_set)
{
	return (bit_to_set>=bytes_of_accumulator*NUM_BITS) ? EOF : SUCCESS ;

	//bit to set goes from 0 to 7 , so for example if an 8 is passed on a 1 byte accumulator error
}

void print_ports(unsigned int port_content,unsigned int counter)
{	
	int temp;
	if(counter)
	{
		temp=(port_content%2);
		port_content/=2;
		print_ports(port_content, --counter); 
		//Funcion recursiva para evitar que los bits se impriman en desorden


		if(counter%4==0)
			printf(" ");
		printf("%u", temp);
		
	}
	
}


