#pragma once

#include <boost/asio/io_service.hpp>
#include <boost/asio/thread_pool.hpp>

using boost::asio::thread_pool, boost::asio::io_context;

namespace programm
{
	class Server
	{
	private:
		static const int port{ 3000 };
		static const int numOfFreads{ 3 };
		int numOfConnectedClients{ 0 };
		thread_pool thread_pool{Server::numOfFreads};

	public:
		Server(const io_context& io_context);

		void Run();

		virtual ~Server();
	};
}