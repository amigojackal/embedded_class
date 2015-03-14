#include <iostream>
#include <stdlib.h>

int main()
{
	std::cout << system("echo 27 > /sys/class/gpio/export") << std::endl;
	std::cout << system("echo \"out\" > /sys/class/gpio/gpio27/direction") << std::endl;
	std::cout << system("cat /sys/class/gpio/gpio27/value") << std::endl;
	std::cout << system("echo 1 > /sys/class/gpio/gpio27/value") << std::endl;
	std::cout << system("cat /sys/class/gpio/gpio27/value") << std::endl;
	std::cout << system("echo 0 > /sys/class/gpio/gpio27/value") << std::endl;
	std::cout << system("echo 1 > /sys/class/gpio/gpio27/value") << std::endl;
	std::cout << system("echo 27 > /sys/class/gpio/unexport") << std::endl;
	std::cout << system("ls") << std::endl;
	
	return 0;
}
