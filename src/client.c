#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

#define HOST    "127.0.0.1"
#define PORT    2000

int main()
{
    int                 server;
    struct sockaddr_in  sv_addr = {AF_INET, htons(PORT), {inet_addr(HOST)}};
    char                mesg[80];
    char                data[80];

    server = socket(AF_INET, SOCK_STREAM, 0);
    connect(server, (struct sockaddr*)&sv_addr, sizeof sv_addr);

    read(server, mesg, sizeof mesg);
    printf("%s", mesg);

    fgets(data, sizeof data, stdin);
    write(server, data, sizeof data);

    read(server, mesg, sizeof mesg);
    printf("%s", mesg);

    close(server);
    return 0;
}
