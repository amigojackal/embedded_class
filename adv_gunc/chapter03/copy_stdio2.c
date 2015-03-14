#include <stdio.h>
/*
 *  test by 
 *  #cat /etc/passwd | ./copy_stdio2 >dest.txt
 * */
int main()
{
    int c;

    while((c = fgetc(stdin)) != EOF)
        fputc(c, stdout);

    exit(0);
}
