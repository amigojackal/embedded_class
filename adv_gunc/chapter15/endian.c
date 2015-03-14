#include <stdio.h>


int main(int argc, char *argv[])
{

	int i, var = 0x12345678, net_order;

	printf("the address of var(%8X) is %8x\n", var, &var);
	for (i = 0; i < 4; i++) {
		printf("byte of var %d is %2X, memeory address :%8x\n",
		i, ((char *)&var)[i], &var + i);
	}
	net_order = htonl(var);
	printf("the address of net_order(%8X) is %8x\n", net_order, &net_order);
	for (i = 0; i < 4; i++) {
		printf("byte of net_order %d is %2X, memeory address :%8x\n",
		i, ((char *)&var)[i], &var + i);
	}
}
