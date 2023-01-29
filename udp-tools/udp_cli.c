// Client side implementation of UDP client-server model 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>

#define PORT 1133
#define MAXLINE 1024
#define MSG_CONFIRM 0 //possibly needed for MAC users

// Driver code
int main(int argc, char **argv) 
{
    
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello Server"; struct sockaddr_in servaddr;
    
    // Creating socket file descriptor
    // SOCK_DGRAM indicates the type of socket to be created which in this case is a UDP 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) 
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE); 
    }

    memset(&servaddr, 0, sizeof(servaddr));
    
    // Filling server information 
    servaddr.sin_family = AF_INET; //IPV4 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    
    int n, len;
    
    sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
    printf("Hello message sent.\n");

    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len); buffer[n] = '\0'; //adds a “\0” character to terminate the received string
    printf("Server : %s\n", buffer);
    
    close(sockfd);
    return 0; 
}
