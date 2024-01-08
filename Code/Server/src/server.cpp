#include "server.hpp"

namespace programm
{
	Server::Server() : 
		numOfConnectedClients{0},
		threadPool{Server::numOfThreads},
		acceptor{this->threadPool.executor()}
	{
		this->ConfigurateAcceptor();

		Accept();
	}

	void Server::Run()
	{
		this->threadPool.join();
	}

	Server::~Server()
	{
	}

	void Server::ConfigurateAcceptor()
	{
		tcp::endpoint serverEndpoint{ boost::asio::ip::address::from_string("127.0.0.1"), Server::port };

		this->acceptor.open(serverEndpoint.protocol());
		this->acceptor.bind(serverEndpoint);
		this->acceptor.listen();
	}

	void Server::Accept()
	{
		this->acceptor.async_accept(make_strand(this->threadPool.executor()), 
			[this](boost::system::error_code ec, boost::asio::ip::tcp::socket connectionSocket) {
				if (!ec)
				{
					boost::asio::write(connectionSocket, buffer(std::string{ "Connection succesfull" }));
					std::cout << "success!\n";
				}

				//std::this_thread::sleep_for(std::chrono::seconds{ 4 });
				Accept();
			});
	}
}