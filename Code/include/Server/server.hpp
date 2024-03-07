 #pragma once

#include <iostream>

#include <boost/asio/io_service.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/asio/strand.hpp>
#include <filesystem>

#include "conection.hpp"

using	boost::system::error_code,
		std::make_shared,
		std::filesystem::create_directory,
		boost::asio::thread_pool,
		boost::asio::io_context,
		boost::asio::ip::tcp,
		boost::asio::buffer,
		boost::asio::async_write,
		boost::asio::make_strand;

namespace AxxonsoftInternProject
{
	namespace SERVER
	{
		class Server
		{
		private:
			int	m_numOfConnectedClients;
			thread_pool	m_threadPool;
			tcp::acceptor m_acceptor;

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