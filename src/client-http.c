#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define HOST    "libdill.org"
#define PORT    "80"

int main()
{
    int                 server;
    struct addrinfo     *host;
    //char              request[]   = "GET / HTTP/1.0\r\nHost: defmacro.com\r\n\r\n";
    char                request[]   = "GET /tutorial-basics.html HTTP/1.0\r\nHost: libdill.org\r\n\r\n";
    char                reply[1024] = {0};

    getaddrinfo(HOST, PORT, NULL, &host);
    server = socket(AF_INET, SOCK_STREAM, 0);
    connect(server, host->ai_addr, host->ai_addrlen);

    write(server, request, sizeof request);

    while (read(server, reply, sizeof reply - 1) > 0) {
        printf("%s", reply);
        memset(reply, 0, sizeof reply);
    }

    close(server);
    return 0;
}
