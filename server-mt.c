#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT    2000
#define QUEUE   5

typedef struct {
    int socket;
    union { struct sockaddr     addr;
            struct sockaddr_in  inaddr; };
} host_t;

void *serve_client(void *_client) {
    host_t client    = *(host_t*)_client;
    char   welcome[] = "+OK Welcome, type your message:\n";
    char   goodbye[] = "+OK Message accepted, goodbye!\n";
    char   data[80]  = {0};

    write(client.socket, welcome, sizeof welcome);
    read(client.socket, data, sizeof data);
    printf("[%s:%d]: %s", inet_ntoa(client.inaddr.sin_addr), ntohs(client.inaddr.sin_port), data);
    write(client.socket, goodbye, sizeof goodbye);
    close(client.socket);
    pthread_exit(NULL);
}

int main()
{
    host_t    server = {.inaddr = {AF_INET, htons(PORT), {INADDR_ANY}}};
    host_t    client;
    pthread_t thread;

    server.socket = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server.socket, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof (int));
    bind(server.socket, &server.addr, sizeof server.addr);
    if (listen(server.socket, QUEUE) == 0)
        puts("listening...");

    while (1) {
        client.socket = accept(server.socket, &client.addr, &(socklen_t){sizeof client.addr});
        pthread_create(&thread, NULL, serve_client, &client);
        pthread_detach(thread);
        sched_yield();
    }

    close(server.socket);
    return 0;
}
