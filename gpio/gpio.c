#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char str[256];
	system("echo 27 > /sys/class/gpio/export");
	system("echo \"out\" > /sys/class/gpio/gpio27/direction");
	system("cat /sys/class/gpio/gpio27/value");
	
	while(true){
		printf("Enter 1 to turn on GPIO27(D1 LED), enter 0 to turn off GPIO27(D1 LED), anything else to quit: ");
		scanf("%s", str);
		if(strcmp(str, "1") == 0){
			system("echo 1 > /sys/class/gpio/gpio27/value");
		}else if(strcmp(str, "0") == 0){
			system("echo 0 > /sys/class/gpio/gpio27/value");
	        }else{
			break;
		}
	}
	system("echo 27 > /sys/class/gpio/unexport");
	printf("END OF TEST \n");
	
	return 0;
}
