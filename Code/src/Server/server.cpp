#include "server.hpp"

namespace AxxonsoftInternProject
{
	namespace SERVER
	{
		Server::Server(const std::string& adress, const std::string& port, const size_t& threadPoolSize) :
			numOfConnectedClients{ 0 },
			threadPool{ threadPoolSize },
			acceptor{ this->threadPool.executor() }
		{
			this->ConfigurateAcceptor(adress, port);

			Accept();
		}

		void Server::Run()
		{
			error_code ec;
			create_directory("./files", ec);

			if (!ec)
			{
				std::cout << "Directory created\n";
			}

			this->threadPool.join();
		}

		Server::~Server()
		{
		}

		void Server::ConfigurateAcceptor(const std::string& adress, const std::string& port)
		{
			tcp::resolver resolver{ this->threadPool.executor() };
			tcp::endpoint serverEndpoint{ *resolver.resolve(adress, port).begin() };

			this->acceptor.open(serverEndpoint.protocol());
			this->acceptor.bind(serverEndpoint);
			this->acceptor.listen();
		}

		void Server::Accept()
		{
			this->acceptor.async_accept(make_strand(this->threadPool.executor()),
				[this](error_code ec, tcp::socket connectionSocket)
				{
					if (!ec)
					{
						std::make_shared<Conection>(std::move(connectionSocket))->Run();
					}

					this->Accept();
				});
		}
	}
}