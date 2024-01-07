#pragma once

#include <boost/asio/io_service.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/asio/ip/tcp.hpp>

using	boost::asio::thread_pool,
		boost::asio::io_context,
		boost::asio::ip::tcp;

namespace programm
{
	class Server
	{
	private:
		static const int	port{ 3000 };
		static const int	numOfThreads{ 3 };
		int					numOfConnectedClients;
		thread_pool			threadPool;
		tcp::acceptor		acceptor;

	public:
		Server();

		virtual ~Server();

	private: 
		void ConfigurateAcceptor();
	};
}