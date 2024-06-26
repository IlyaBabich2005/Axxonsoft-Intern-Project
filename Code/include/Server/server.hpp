 #pragma once

#include <iostream>

#include <boost/asio/io_service.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/asio/strand.hpp>
#include <filesystem>

#include "conection.hpp"

namespace AxxonsoftInternProject
{
	namespace SERVER
	{
		class Server
		{
		private:
			boost::asio::thread_pool m_threadPool;
			boost::asio::ip::tcp::acceptor m_acceptor;
			std::shared_ptr<DigestManager> m_digestManager;

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