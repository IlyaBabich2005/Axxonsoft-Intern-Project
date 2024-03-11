#pragma once

#include <array>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/impl/write.hpp>

#include "HTTPRequestParser.hpp"
#include "HTTPRequestHandler.hpp"
#include "HTTPReplySerializer.hpp"

namespace http = AxxonsoftInternProject::http;
namespace stock = AxxonsoftInternProject::http::stock;
namespace asio = boost::asio;
namespace system = boost::system;
namespace ip = asio::ip;

namespace AxxonsoftInternProject
{
	namespace SERVER
	{
		class Conection : public std::enable_shared_from_this<Conection>
		{
		private:
			static const size_t m_bufferSize{ 10 * 1024};
			std::array<char, Conection::m_bufferSize> m_incomeBuffer;
			std::shared_ptr<http::HTTPRequest> m_request;
			std::shared_ptr<http::HTTPReply> m_reply;
			http::HTTPRequestParcer m_parcer;
			http::HTTPRequestHandler m_handler;
			http::HTTPReplySerializer m_serializer;
			ip::tcp::socket m_connectionSocket;

		private:
			void read();
			void write();

		public:
			Conection(ip::tcp::socket connectionSocket);

			void Run();
		};
	}
}
