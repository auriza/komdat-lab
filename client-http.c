#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define HOST    "162.213.33.66"
#define PORT    80

int main()
{
    int                 server;
    struct sockaddr_in  sv_addr     = {AF_INET, htons(PORT), {inet_addr(HOST)}};
    char                request[]   = "GET / HTTP/1.0\nHost: xubuntu.org\n\n";
    char                reply[1024] = {0};


    server = socket(AF_INET, SOCK_STREAM, 0);
    connect(server, (struct sockaddr*)&sv_addr, sizeof sv_addr);

    write(server, request, sizeof request);

    while (read(server, reply, sizeof reply - 1) > 0) {
        printf("%s", reply);
        memset(reply, 0, sizeof reply);
    }

    close(server);
    return 0;
}
