#include <iostream>

#include <boost/asio/io_context.hpp>
//#include <boost/asio/impl/connect.hpp>

#include "HTTPReplyParser.hpp"
#include "ClientConnection.hpp"
#include "CommandParcer.hpp"
#include "CommandHandler.hpp"

using //boost::asio::async_connect,
	  boost::asio::io_context,
	  std::string;

namespace AxxonsoftInternProject
{
	namespace Client
	{
		class Client
		{
		private: 
			io_context context;
			tcp::endpoint serverEndpoint;
			tcp::socket connectionSocket;
			CommandParcer parcer;
			shared_ptr<Command> command;
			shared_ptr<HTTPRequest> outputRequest;
			CommandHandler handler;

		private:
			void ReadCommand();
			void Connect();

		public:
			Client(string serverIP, string serverPort);
			
			void Run();
			
		};
	}
}