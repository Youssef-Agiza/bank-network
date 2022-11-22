#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <thread>

#define PORT 8080
#define BUFFER_SIZE 1024

void emit_error(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void send_msg(int client_fd)
{

	char msg[BUFFER_SIZE] = {0};
	std::cout << ">";
	std::string data;
	std::getline(std::cin, data);
	memset(&msg, 0, sizeof(msg));
	strcpy(msg, data.c_str());

	send(client_fd, msg, strlen(msg), 0);
}

void recv_msg(int client_fd)
{

	while (1)
	{

		char msg[BUFFER_SIZE] = {0};
		read(client_fd, msg, BUFFER_SIZE);

		std::cout << msg << std::endl;

		std::cout << ">";
	}
}

int main(int argc, char const *argv[])
{
	int server_fd, new_socket;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		emit_error("socket failed");

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
				   &opt, sizeof(opt)))
		emit_error("setsockopt");

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address,
			 sizeof(address)) < 0)
		emit_error("bind failed");
	if (listen(server_fd, 3) < 0)
		emit_error("listen");

std::cout << "Waiting for client to connect at port " << PORT << "..."<< std::endl;
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
							 (socklen_t *)&addrlen)) < 0)
		emit_error("accept");

	// create threads to recieve messages only
	std::thread t1(recv_msg, new_socket);

	while (true)
		send_msg(new_socket);

	t1.join();

	return 0;
}
