#include "server.hpp"

namespace programm
{
	Server::Server(const io_context& io_context)
	{
	}

	void Server::Run()
	{

	}

	Server::~Server()
	{
		this->thread_pool.join();
	}
}