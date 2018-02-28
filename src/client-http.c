#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

//#define HOST    "38.109.180.24"
#define HOST    "192.30.252.153"
#define PORT    80

int main()
{
    int                 server;
    struct sockaddr_in  sv_addr     = {AF_INET, htons(PORT), {inet_addr(HOST)}};
    //char                request[]   = "GET / HTTP/1.0\r\nHost: defmacro.com\r\n\r\n";
    char                request[]   = "GET /tutorial-basics.html HTTP/1.0\r\nHost: libdill.org\r\n\r\n";
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
