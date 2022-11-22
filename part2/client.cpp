#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <thread>
#define PORT 8080
#define BUFFER_SIZE 1024

void send_msg(int client_fd)
{

    char msg[BUFFER_SIZE] = {0};
    std::cout << ">";
    // take input from stdin
    std::string data;
    std::getline(std::cin, data);
    memset(&msg, 0, sizeof(msg));
    strcpy(msg, data.c_str());

    // send the message
    send(client_fd, msg, strlen(msg), 0);
}

void recv_msg(int client_fd)
{
    while (1)
    {

        char msg[BUFFER_SIZE] = {0};
        read(client_fd, msg, BUFFER_SIZE);

        std::cout << msg << std::endl;
        std::cout << "\n";
    }
}

void emit_error(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char const *argv[])
{
    int sock = 0, client_fd;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        emit_error("\n Socket creation error\n");

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
        emit_error("\nInvalid address/ Address not supported\n");



    if ((client_fd = connect(sock, (struct sockaddr *)&serv_addr,
                             sizeof(serv_addr))) < 0)
        emit_error("\nConnection Failed\n");

    // use threads to recv and send messages inifinitely
    std::thread t2(recv_msg, sock);
    t2.detach();

    while (true)
        send_msg(sock);

    // closing the connected socket
    close(client_fd);
    return 0;
}
