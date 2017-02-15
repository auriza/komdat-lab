#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

#define HOST    0x7f000001  // 127.0.0.1
#define PORT    2000

int main()
{
    int                 server;
    struct sockaddr_in  server_addr = {AF_INET, htons(PORT), {htonl(HOST)}};
    char                resp[80];
    char                data[80];

    server = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(server, (struct sockaddr*)&server_addr, sizeof(server_addr)) == 0)
        puts("connected...");

    recv(server, resp, sizeof(resp), 0);
    printf("%s", resp);

    fgets(data, sizeof(data), stdin);
    send(server, data, sizeof(data), 0);

    recv(server, resp, sizeof(resp), 0);
    printf("%s", resp);

    close(server);
    return 0;
}
