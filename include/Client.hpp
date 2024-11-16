#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <sstream>
# include <string>
# include <typeinfo>
# include <Utils.hpp>

# ifndef DEBUG
#  define DEBUG 0
# endif

class Client
{
	private:

	protected:
		
	public:
		Client();
		// Client& operator=(Client const& rhs);
		// Client(Client const& rhs);
		~Client();
};

// std::ostream& operator << (std::ostream& os, Client& rhs);

#endif // CLIENT_HPP