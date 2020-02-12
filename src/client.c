#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define HOST    "localhost"
#define PORT    "2000"

int main()
{
    struct addrinfo     *host;
    int                 server;
    char                mesg[80];
    char                data[80];

    getaddrinfo(HOST, PORT, NULL, &host);
    server = socket(AF_INET, SOCK_STREAM, 0);
    connect(server, host->ai_addr, host->ai_addrlen);

    read(server, mesg, sizeof mesg);
    printf("%s", mesg);

    fgets(data, sizeof data, stdin);
    write(server, data, sizeof data);

    read(server, mesg, sizeof mesg);
    printf("%s", mesg);

    close(server);
    return 0;
}
