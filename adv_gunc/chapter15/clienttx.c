/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    int sockfd, txfd;
    int len;
    struct sockaddr_in address;
    int result;
    char ch = 'A';
    char *remote = "127.0.0.1";

    if (argc < 2) {
	printf("usage: %s <file> <server_ip>\n");
	exit(0);
    }
    if (argc >= 3)
	remote = argv[2];

    if ((txfd = open(argv[1], O_RDONLY)) == -1) {
	perror("can not open");
	exit(0);
    }
/*  Create a socket for the client.  */

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

/*  Name the socket, as agreed with the server.  */

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(remote);
    address.sin_port = htons(9734);
    len = sizeof(address);

/*  Now connect our socket to the server's socket.  */

    result = connect(sockfd, (struct sockaddr *)&address, len);

    if(result == -1) {
        perror("oops: client3");
        exit(1);
    }

/*  We can now read/write via sockfd.  */

    while (read(txfd, &ch, 1) == 1)
	if (write(sockfd, &ch, 1) != 1)
		goto sys_err;
   close(txfd);
   close(sockfd);
   return 0;
sys_err:
    perror("sys ");
    exit(-1);
}
