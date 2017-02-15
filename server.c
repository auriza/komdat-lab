#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT    2000
#define QUEUE   5

int main()
{
    int                 server;
    int                 client;
    struct sockaddr_in  server_addr = {AF_INET, htons(PORT), {INADDR_ANY}};
    struct sockaddr_in  client_addr;
    char                hello[]  = "+ok hello, type your message:\n";
    char                bye[]    = "+ok bye!\n";
    char                data[80] = {0};

    server = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    bind(server, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (listen(server, QUEUE) == 0)
        puts("listening...");

    while (1) {
        client = accept(server, (struct sockaddr*)&client_addr, &(socklen_t){sizeof(client_addr)});
        send(client, hello, sizeof(hello), 0);

        memset(data, 0, sizeof(data));
        recv(client, data, sizeof(data), 0);
        printf("[%x:%x]: %s", ntohl(client_addr.sin_addr.s_addr), ntohs(client_addr.sin_port), data);

        send(client, bye, sizeof(bye), 0);
        close(client);
    }

    close(server);
    return 0;
}
