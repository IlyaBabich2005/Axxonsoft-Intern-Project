#include <iostream>

#include <boost/asio/io_context.hpp>
//#include <boost/asio/impl/connect.hpp>

#include "HTTPReplyParser.hpp"
#include "ClientConnection.hpp"
#include "CommandParcer.hpp"
#include "CommandHandler.hpp"

using std::cout,
	  std::getline,
	  std::cin,
	  std::make_shared,
	  std::move,
	  boost::asio::io_context,
	  std::string;

namespace AxxonsoftInternProject
{
	namespace Client
	{
		class Client
		{
		private: 
			io_context m_context;
			tcp::endpoint m_serverEndpoint;
			tcp::socket m_connectionSocket;
			CommandParcer m_parcer;
			shared_ptr<Command> m_command;
			shared_ptr<HTTPRequest> m_outputRequest;
			CommandHandler m_handler;

		private:
			void readCommand();
			void connect();

		public:
			Client(string serverIP, string serverPort);
			
			void Run();
			
		};
	}
}