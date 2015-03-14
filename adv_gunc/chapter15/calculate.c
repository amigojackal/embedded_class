/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
int calculate(char *str, int *result)
{
	char *h, *x, *y, *ops;
	int a, b, rev = 0;

	if ((h = strdup(str)) == NULL)
		return -1;
	str = h;
	x = strsep(&str, " ");
	ops = strsep(&str, " ");
	y = strsep(&str, " ");
	
	a = atoi(x);
	b = atoi(y);

	//fprintf(stderr, "%d, %c, %d\n", a, *ops, b);
	switch (*ops) {
	case '+':
		*result = a + b;
		break;
	case '-':
		*result = a - b;
		break;
	case '*':
		*result = a * b;
		break;
	case '/':
		*result = a / b;
		break;
	case '%':
		*result = a % b;
		break;
	default:
		rev = -1;
	}
	free(h);
	return rev;
}

int main()
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

/*  Remove any old socket and create an unnamed socket for the server.  */

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

/*  Name the socket.  */

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(9734);
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

/*  Create a connection queue and wait for clients.  */

    listen(server_sockfd, 5);
    while(1) {
	char buf[1024];
	int result;
        printf("server waiting\n");

/*  Accept a connection.  */

        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, 
            (struct sockaddr *)&client_address, &client_len);

/*  We can now read/write to client on client_sockfd.  */

        read(client_sockfd, buf, sizeof(buf));
	if (calculate(buf, &result) == -1)
		sprintf(buf, "error format! test example: 1 + 2\n");
	else
		sprintf(buf, "ans:%d\n", result);
        write(client_sockfd, buf, strlen(buf));
        close(client_sockfd);
    }
}

