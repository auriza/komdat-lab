#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT    2000
#define QUEUE   5

int main()
{
    int                 server;
    int                 client;
    struct sockaddr_in  sv_addr = {AF_INET, htons(PORT), {INADDR_ANY}};
    struct sockaddr_in  cl_addr;
    char                welcome[] = "+OK Welcome, type your message:\n";
    char                goodbye[] = "+OK Message accepted, goodbye!\n";
    char                data[80]  = {0};

    server = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof (int));
    bind(server, (struct sockaddr*)&sv_addr, sizeof sv_addr);
    if (listen(server, QUEUE) == 0)
        puts("listening...");

    #pragma omp parallel private(client, cl_addr, data) num_threads(8)
    while (1) {
        client = accept(server, (struct sockaddr*)&cl_addr, &(socklen_t){sizeof cl_addr});
        write(client, welcome, sizeof welcome);

        memset(data, 0, sizeof data);
        read(client, data, sizeof data);
        printf("[%s:%d]: %s", inet_ntoa(cl_addr.sin_addr), ntohs(cl_addr.sin_port), data);

        write(client, goodbye, sizeof goodbye);
        close(client);
    }

    close(server);
    return 0;
}
