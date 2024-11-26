#include "Server.hpp"
#include "Command.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <algorithm>
#include <cerrno>  // For errno
#include <cstring> // For strerror
#include <cstdio>  // For perror

Server::Server(int port)
{
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
	{
		perror("socket");
		exit(1);
	}

	setNonBlocking(server_fd);

	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port);

	if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("bind");
		close(server_fd);
		exit(1);
	}

	if (listen(server_fd, 100) < 0)
	{
		perror("listen");
		close(server_fd);
		exit(1);
	}

	struct pollfd server_pfd =
	{server_fd, POLLIN, 0};
	poll_fds.push_back(server_pfd);

	pthread_mutex_init(&clients_mutex, NULL);
	pthread_mutex_init(&channels_mutex, NULL);
}

Server::~Server()
{
	pthread_mutex_destroy(&clients_mutex);
	pthread_mutex_destroy(&channels_mutex);
	close(server_fd);
}

void Server::setNonBlocking(int fd)
{
	fcntl(fd, F_SETFL, O_NONBLOCK);
}

void Server::handleNewConnection()
{
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
	if (client_fd < 0)
	{
		perror("accept");
		return;
	}
	setNonBlocking(client_fd);
	struct pollfd pfd = {client_fd, POLLIN, 0};
	poll_fds.push_back(pfd);

	pthread_mutex_lock(&clients_mutex);
	clients[client_fd] = Client(client_fd);
	pthread_mutex_unlock(&clients_mutex);

	std::cout << "New client connected: " << client_fd << std::endl;

	pthread_create(&clients[client_fd].thread, NULL, handleClient, &clients[client_fd]);
}

void* Server::handleClient(void* arg)
{
	Client* client = static_cast<Client*>(arg);
	char buffer[512];
	while (true)
	{
		int nbytes = read(client->fd, buffer, sizeof(buffer) - 1);
		if (nbytes <= 0)
		{
			if (nbytes < 0) perror("read");
			close(client->fd);

			pthread_mutex_lock(&this->clients_mutex);
			clients.erase(client->fd);
			pthread_mutex_unlock(&clients_mutex);

			break;
		}
		buffer[nbytes] = '\0';
		client->buffer += buffer;

		// Process commands
		size_t pos;
		while ((pos = client->buffer.find("\r\n")) != std::string::npos)
		{
			std::string command = client->buffer.substr(0, pos);
			client->buffer.erase(0, pos + 2);
			std::cout << "Received command from " << client->fd << ": " << command << std::endl;

			pthread_mutex_lock(&channels_mutex);
			Commands::handleCommand(command, client, channels);
			pthread_mutex_unlock(&channels_mutex);
		}
	}
	return NULL;
}

void Server::run()
{
	while (true)
	{
		int poll_count = poll(&poll_fds[0], poll_fds.size(), -1);
		if (poll_count < 0)
		{
			perror("poll");
			break;
		}

		for (size_t i = 0; i < poll_fds.size(); ++i)
		{
			if (poll_fds[i].revents & POLLIN)
			{
				if (poll_fds[i].fd == server_fd)
				{
					handleNewConnection();
				}
			}
		}
	}
}