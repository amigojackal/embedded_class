#include <stdio.h>
#include "foo.h"

int main(int argc, char *argv[])
{
	foo_test();
	printf("%s\n", __FUNCTION__);
}
