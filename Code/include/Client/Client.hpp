#include <iostream>

#include <boost/asio/io_context.hpp>

#include "HTTPReplyParser.hpp"
#include "ClientConnection.hpp"
#include "CommandParcer.hpp"
#include "CommandHandler.hpp"

namespace AxxonsoftInternProject
{
	namespace Client
	{
		class Client
		{
		private: 
			asio::io_context m_context;
			ip::tcp::endpoint m_serverEndpoint;
			ip::tcp::socket m_connectionSocket;
			CommandParcer m_parcer;
			std::shared_ptr<Command> m_command;
			std::shared_ptr<http::HTTPRequest> m_outputRequest;
			CommandHandler m_handler;

		private:
			void readCommand();
			void connect();

		public:
			Client(std::string serverIP, std::string serverPort);
			
			void Run();
			
		};
	}
}