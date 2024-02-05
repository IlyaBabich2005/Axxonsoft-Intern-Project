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
				[this](boost::system::error_code ec, boost::asio::ip::tcp::socket connectionSocket)
				{
					if (!ec)
					{
						write(connectionSocket, buffer(std::string{ "hello world" }));
						std::cout << "success!\n";
					}

					//std::this_thread::sleep_for(std::chrono::seconds{ 4 });
					this->Accept();
				});
		}
	}
}