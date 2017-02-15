#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT    2000
#define QUEUE   5
#define T       8

void *serve_client(void *);

int main()
{
    int                 server;
    struct sockaddr_in  server_addr = {AF_INET, htons(PORT), {INADDR_ANY}};
    pthread_t           thread[T];
    int                 i;

    server = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    bind(server, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server, QUEUE);
    puts("listening...");

    for (i = 0; i < T; i++)
        pthread_create(&thread[i], NULL, serve_client, &server);
    for (i = 0; i < T; i++)
        pthread_join(thread[i], NULL);

    close(server);
    return 0;
}

void *serve_client(void *arg) {
    int                 server = *(int*)arg;
    int                 client;
    struct sockaddr_in  client_addr;
    char                welcome[] = "+ok welcome, type your message:\n> ";
    char                bye[]     = "+ok bye!\n";
    char                data[80];

    while (1) {
        client = accept(server, (struct sockaddr*)&client_addr, &(socklen_t){sizeof(client_addr)});
        send(client, welcome, sizeof(welcome), 0);
        memset(data, 0, sizeof(data));
        recv(client, data, sizeof(data), 0);
        printf("[%s:%d]: %s", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), data);
        send(client, bye, sizeof(bye), 0);
        close(client);
    }
    pthread_exit(NULL);
}
