#pragma once

#include <iostream>

#include <boost/asio/io_service.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>

using	boost::asio::thread_pool,
		boost::asio::io_context,
		boost::asio::ip::tcp,
		boost::asio::buffer,
		boost::asio::async_write,
		boost::asio::make_strand;

namespace programm
{
	class Server
	{
	private:
		int					numOfConnectedClients;
		thread_pool			threadPool;
		tcp::acceptor		acceptor;

	public:
		Server(const std::string& adress, const std::string& port, const size_t& threadPoolSize);

		void Run();

		virtual ~Server();

	private: 
		void ConfigurateAcceptor(const std::string& adress, const std::string& port);

		void Accept();
	};
}