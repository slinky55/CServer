#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


void error(char const* msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char** argv)
{
    int sfd, port, n;
    
    struct sockaddr_in serv_addr;
    struct hostent* server;

    char buffer[256];

    if (argc < 3)
    {
        printf("Usage: %s hostname port\n", argv[0]);
        exit(1);
    }

    port = atoi(argv[2]);
    sfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sfd < 0)
    {
        error("Failed to open socket");
    }

    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        error("No such host");
    }

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char*)server->h_addr,
          (char*)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(port);
    
    if (connect(sfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        error("Failed to connect to host");
    }

    printf("Enter message to send: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    
    n = write(sfd, buffer, strlen(buffer));

    if (n < 0)
    {    
        error("Failed to write to socket");
    }

    bzero(buffer, 256);
    n = read(sfd, buffer, 255);

    if (n < 0)
    {
        error("Failed to read from socket");
    }

    printf("%s\n", buffer);
    close(sfd);


    return 0;
}

