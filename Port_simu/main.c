#include <stdio.h>
#include <stdlib.h>
#include "port_functions.h"


int main(void) {
	
	static union accumulator accumulatord; //HAD TO INCLUDE THE ACCUMULATOR IN MAIN TO BE ABLE TO
	//Test the programs, the idea would be for this to be in port_functions.c
	printf("The size of accumulator is %lu \n",sizeof(accumulatord));
	if(maskmanage(ACCD_ADR, SIZE_ACCD /NUM_BITS, "0000000000000000",&bitset))
		printf("ERROR\n");
	print_ports(ACCD,SIZE_ACCD);printf("\n");
	
	if(maskmanage(ACCD_ADR, SIZE_ACCD/NUM_BITS, "   1111     0100     1000   1001",&bitset)) //also allows spaces in mask
		printf("ERROR\n");
	print_ports(ACCD,SIZE_ACCD);printf("\n");
	
	if(maskmanage(&ACCA, SIZE_ACCAB/NUM_BITS, " 1111   1111",&bitToggle))
		printf("ERROR\n");
	print_ports(ACCD,SIZE_ACCD);printf("\n");
	
	
	return (0);
}

