#include <iostream>
#include <memory>

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/basic_streambuf.hpp>
#include <boost/asio.hpp>

#include "HTTPReplyParser.hpp"
#include "CommandParcer.hpp"
#include "CommandHandler.hpp"
#include "HTTPReplyHandler.hpp"
#include "HTTPRequestSerializer.hpp"

namespace AxxonsoftInternProject
{
	namespace Client
	{
		class Client : public std::enable_shared_from_this<Client>
		{
		private:
			static const std::size_t m_bufferSize{ 10 * 1024 };
			std::array<char, Client::m_bufferSize> m_incomeBuffer;
			boost::asio::ip::tcp::endpoint m_serverEndpoint;
			boost::asio::ip::tcp::socket m_connectionSocket;
			CommandParcer m_commandParcer;
			CommandHandler m_commandHandler;
			std::shared_ptr<Command> m_command;
			std::shared_ptr<http::HTTPRequest> m_request;
			std::shared_ptr<http::HTTPReply> m_reply;
			http::HTTPReplyHandler m_replyHandler;
			http::HTTPReplyParser m_replyParcer;
			http::HTTPRequestSerializer m_serializer;

		private:
			void readCommand();
			void connect();
			void writeRequest();
			void readReply();

		public:
			Client(std::string serverIP, std::string serverPort, boost::asio::io_context& context);

			void Run();

		};
	}
}