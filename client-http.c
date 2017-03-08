#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

#define HOST    "162.213.33.66"
#define PORT    80
#define BUFSZ   4096


int main()
{
    int                 server;
    struct sockaddr_in  sv_addr      = {AF_INET, htons(PORT), {inet_addr(HOST)}};
    char                request[]    = "GET / HTTP/1.1\nHost: xubuntu.org\n\n";
    char                reply[BUFSZ] = {0};
    char*               reply_ptr;
    int                 nread, n;

    server = socket(AF_INET, SOCK_STREAM, 0);
    connect(server, (struct sockaddr*)&sv_addr, sizeof sv_addr);

    write(server, request, sizeof request);

    reply_ptr = reply;
    nread = BUFSZ;

    while ((n = read(server, reply_ptr, nread)) > 0) {
        reply_ptr += n;
        nread -= n;
    }

    puts(reply);

    close(server);
    return 0;
}
