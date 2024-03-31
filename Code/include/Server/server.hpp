 #pragma once

#include <iostream>

#include <boost/asio/io_service.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/asio/strand.hpp>
#include <filesystem>

#include "conection.hpp"
#include "SessionManager.hpp"

namespace AxxonsoftInternProject
{
	namespace SERVER
	{
		class Server
		{
		private:
			OfConnectedClients;
			boost::asio::thread_pool m_threadPool;
			boost::asio::ip::tcp::acceptor m_acceptor;
			SessionManager m_sessionManager;

		private:
			void configurateAcceptor(const std::string& adress, const std::string& port);

			void accept();

		public:
			Server(const std::string& adress, const std::string& port, const size_t& threadPoolSize);

			void Run();

			virtual ~Server();
		};
	}
}