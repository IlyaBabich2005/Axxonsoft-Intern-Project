#include "server.hpp"

namespace AxxonsoftInternProject
{
	namespace SERVER
	{
		Server::Server(const std::string& adress, const std::string& port, const std::size_t& threadPoolSize) :
			m_numOfConnectedClients{ 0 },
			m_threadPool{ threadPoolSize },
			m_acceptor{ m_threadPool.executor() }
		{
			configurateAcceptor(adress, port);

			accept();
		}

		void Server::Run()
		{
			system::error_code ec;
			filesystem::create_directory(Configuration::g_serverRootDirectory, ec);

			if (!ec)
			{
				std::cout << stock::messages::g_directoryCreated << "\n";
			}

			m_threadPool.join();
		}

		Server::~Server()
		{
		}

		void Server::configurateAcceptor(const string& adress, const string& port)
		{
			ip::tcp::resolver resolver{ m_threadPool.executor() };
			ip::tcp::endpoint serverEndpoint{ *resolver.resolve(adress, port).begin() };

			m_acceptor.open(serverEndpoint.protocol());
			m_acceptor.bind(serverEndpoint);
			m_acceptor.listen();
		}

		void Server::accept()
		{
			m_acceptor.async_accept(make_strand(m_threadPool.executor()),
				[this](system::error_code ec, ip::tcp::socket connectionSocket)
				{
					if (!ec)
					{
						std::make_shared<Conection>(std::move(connectionSocket))->Run();
					}

					accept();
				});
		}
	}
}