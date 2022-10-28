#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(char const* msg)
{
    perror(msg);
    exit(1);
}


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Usage: %s port\n", argv[0]);
        exit(1);
    }

    printf("Starting server...\n");

    int sfd, newSfd, port;
    char buffer[265];

    struct sockaddr_in serv_addr, client_addr;

    int n;

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0)
    {
        error("Failed to open socket");
    }

    bzero((char*)&serv_addr, sizeof(serv_addr));
    port = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    if (bind(sfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        error("Failed to bind port");
    }

    listen(sfd, 5);

    printf("Listening on port %d\n", port);

    socklen_t clientLen = sizeof(client_addr);
    newSfd = accept(sfd, (struct sockaddr*)&client_addr, &clientLen);
    if (newSfd < 0)
    {
        error("Failed on accept");
    }

    bzero(buffer, 256);
    n = read(newSfd, buffer, 255);
    if (n < 0)
    {
        error("Failed to read from socket");
    }

    printf("Message: %s", buffer);
    n = write(newSfd, "Received!", 9);

    if (n < 0)
    {
        error("Failed to send message to client");
    }

    close(newSfd);
    close(sfd);


    return 0;
}
