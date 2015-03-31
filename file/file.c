#include <stdio.h>

int main()
{
	FILE *fd;
	char str[256];

	fd = fopen("load","r");
	while(fd>0 && !feof(fd)){
		fgets(str,256,fd);
		if(!feof(fd)) printf("%s", str);
	}
	fclose(fd);

	fd = fopen("load","a");
	fputs("testo\n", fd);
	fclose(fd);
	return 0;
}
