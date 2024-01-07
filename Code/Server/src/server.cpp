#include "server.hpp"

namespace programm
{
	Server::Server() : 
		numOfConnectedClients{0},
		threadPool{Server::numOfThreads},
		acceptor{this->threadPool.executor()}
	{
		tcp::endpoint serverEndpoint{ tcp::v4(), Server::port };

		this->acceptor.open(serverEndpoint.protocol());
		this->acceptor.bind(serverEndpoint);
		this->acceptor.listen();
	}

	Server::~Server()
	{
		this->threadPool.join();
	}

	void Server::ConfigurateAcceptor()
	{

	}
}