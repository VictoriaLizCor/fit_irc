#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <string>
#include <vector>
#include <pthread.h>
#include "Client.hpp"

# ifndef DEBUG
#  define DEBUG 0
# endif


class Channel
{
	public:
		std::string name;
		std::vector<Client*> members;
		pthread_mutex_t mutex;

		Channel(const std::string &name);
		~Channel();
		void addMember(Client *client);
		void removeMember(Client *client);
		void broadcast(const std::string &message, Client *exclude = NULL);
};


#endif // CHANNEL_HPP