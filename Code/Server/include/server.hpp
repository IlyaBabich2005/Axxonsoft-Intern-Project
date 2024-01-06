#pragma once

#include <boost/asio/io_service.hpp>

namespace programm
{
	class Server
	{
	private:
		int port = 3000;
		bool isActive = false;
		int connectedUsers = 0;

	public:
		Server(int port);

		//void Run();

		//virtual ~Server();
	};
}