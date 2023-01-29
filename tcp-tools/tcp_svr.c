#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAX 1000
#define ACK "ACK"
#define SA struct sockaddr

void func(int sockfd)
{
	char buff[MAX];

	for (;;)
	{

		bzero(buff, MAX);
		

		// read the message from client and copy it in buffer
		read(sockfd, buff, sizeof(buff));

		// print buffer which contains the client contents
		if (buff[0] != 0)
			printf("From client: %s\n", buff);

		if (strncmp("exit", buff, 4) == 0)
			break;
	}
}

// Driver function
int main(int argc, char **argv)
{
	struct sockaddr_storage from;
	int err, new_sock, sock;
	unsigned int adl;

	char cliIPtext[MAX], cliPortText[MAX];
	struct addrinfo req, *list;

	bzero((char *)&req, sizeof(req));

	// requesting an IPv4 type of communication
	req.ai_family = AF_INET;
	req.ai_socktype = SOCK_STREAM;
	req.ai_flags = AI_PASSIVE; // local address

	err = getaddrinfo(NULL, argv[1], &req, &list);

	if (err)
	{
		printf("Failed to get local address, error: %s\n", gai_strerror(err));
		exit(1);
	}

	sock = socket(list->ai_family, list->ai_socktype, list->ai_protocol);

	if (sock == -1)
	{
		perror("Failed to open socket");
		freeaddrinfo(list);
		exit(1);
	}

	if (bind(sock, (struct sockaddr *)list->ai_addr, list->ai_addrlen) == -1)
	{
		perror("Bind failed");
		close(sock);
		freeaddrinfo(list);
		exit(1);
	}

	char buf[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, list->ai_addr, buf, sizeof(buf));
	printf("IP address: %s\n", buf);

	freeaddrinfo(list);
	listen(sock, SOMAXCONN);
	puts("Accepting TCP connections (IPv6/IPv4). Use CTRL+C to terminate the server");

	adl = sizeof(from);

	for (;;)
	{
		// Accept the data packet from client and verification
		new_sock = accept(sock, (SA *)&from, &adl);

		if (new_sock < 0)
		{
			printf("Server accept failed...\n");
			exit(0);
		}

		if (!fork())
		{
			close(sock);

			getnameinfo((struct sockaddr *)&from, adl, cliIPtext, MAX, cliPortText, MAX, NI_NUMERICHOST | NI_NUMERICSERV);
			printf("New connection from %s, port number %s\n", cliIPtext, cliPortText);

			func(new_sock);
			printf("Server Exit...\n");
		}
		close(new_sock);
		break;
	}
	close(sock);
	exit(0);
}
