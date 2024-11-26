#include <iostream>
#include "Client.hpp"
#include "Server.hpp"

int main()
{
	Server server(6667);
	server.run();
	return (0);
}