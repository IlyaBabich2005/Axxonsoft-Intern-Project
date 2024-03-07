#include "server.hpp"

namespace AxxonsoftInternProject
{
	namespace SERVER
	{
		Server::Server(const string& adress, const string& port, const size_t& threadPoolSize) :
			m_numOfConnectedClients{ 0 },
			m_threadPool{ threadPoolSize },
			m_acceptor{ m_threadPool.executor() }
		{
			configurateAcceptor(adress, port);

			accept();
		}

		void Server::Run()
		{
			error_code ec;
			create_directory(g_serverRootDirectory, ec);

			if (!ec)
			{
				cout << "Directory created\n";
			}

			m_threadPool.join();
		}

		Server::~Server()
		{
		}

		void Server::configurateAcceptor(const string& adress, const string& port)
		{
			tcp::resolver resolver{ m_threadPool.executor() };
			tcp::endpoint serverEndpoint{ *resolver.resolve(adress, port).begin() };

			m_acceptor.open(serverEndpoint.protocol());
			m_acceptor.bind(serverEndpoint);
			m_acceptor.listen();
		}

		void Server::accept()
		{
			m_acceptor.async_accept(make_strand(m_threadPool.executor()),
				[this](error_code ec, tcp::socket connectionSocket)
				{
					if (!ec)
					{
						make_shared<Conection>(move(connectionSocket))->Run();
					}

					accept();
				});
		}
	}
}