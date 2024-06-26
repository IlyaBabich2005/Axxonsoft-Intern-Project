#include "server.hpp"

namespace AxxonsoftInternProject
{
	namespace SERVER
	{
		Server::Server(const std::string& adress, const std::string& port, const std::size_t& threadPoolSize) :
			m_threadPool{ threadPoolSize },
			m_acceptor{ m_threadPool.executor() },
			m_digestManager{ new DigestManager() }
		{
			configurateAcceptor(adress, port);

			accept();
		}

		void Server::Run()
		{
			boost::system::error_code ec;
			std::filesystem::create_directory(Configuration::g_serverRootDirectory, ec);

			if (!ec)
			{
				std::cout << AxxonsoftInternProject::http::stock::messages::g_directoryCreated << "\n";
			}

			m_threadPool.join();
		}

		Server::~Server()
		{
		}

		void Server::configurateAcceptor(const std::string& adress, const std::string& port)
		{
			boost::asio::ip::tcp::resolver resolver{ m_threadPool.executor() };
			boost::asio::ip::tcp::endpoint serverEndpoint{ *resolver.resolve(adress, port).begin() };

			m_acceptor.open(serverEndpoint.protocol());
			m_acceptor.bind(serverEndpoint);
			m_acceptor.listen();
		}

		void Server::accept()
		{
			m_digestManager->Update();

			m_acceptor.async_accept(make_strand(m_threadPool.executor()),
				[this](boost::system::error_code ec, boost::asio::ip::tcp::socket connectionSocket)
				{
					if (!ec)
					{
						std::make_shared<Conection>(std::move(connectionSocket), m_digestManager)->Run();
					}

					accept();
				});
		}
	}
}