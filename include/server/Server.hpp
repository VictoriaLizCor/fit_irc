#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>
#include <map>
#include <poll.h>
#include <pthread.h>
#include "Client.hpp"
#include "Channel.hpp"

class Server
{
	private:
		int server_fd;
		std::vector<struct pollfd> poll_fds;
		std::map<int, Client> clients;
		std::map<std::string, Channel> channels;
		pthread_mutex_t clients_mutex;
		pthread_mutex_t channels_mutex;

		void setNonBlocking(int fd);
		void handleNewConnection();
		static void* handleClient(void* arg);

	public:
		Server(int port);
		~Server();
		void run();
};

/*OPtional?*/
struct ClientHandlerArgs
{
    Server* server;
    Client* client;
};

#endif // SERVER_H