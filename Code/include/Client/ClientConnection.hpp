#pragma once

#include <array>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/impl/write.hpp>

#include "HTTPReplyParser.hpp"
#include "HTTPReplyHandler.hpp"
#include "HTTPRequestSerializer.hpp"
#include "HTTPReply.hpp"

namespace http = AxxonsoftInternProject::http;

using	
		boost::asio::async_write,
		boost::asio::ip::tcp,
		boost::asio::buffer,
		boost::system::error_code,
		http::HTTPReplyParser,
		http::HTTPReplyHandler,
		http::HTTPRequest,
		http::HTTPReply,
		http::ParsingStatus,
		http::HTTPRequestSerializer,
		std::enable_shared_from_this,
		std::cout,
		std::move,
		std::size_t,
		std::array;

namespace AxxonsoftInternProject
{
	namespace Client
	{
		class ClientConection : public enable_shared_from_this<ClientConection>
		{
		private:
			static const size_t m_bufferSize{ 10 * 1024 };
			array<char, ClientConection::m_bufferSize> m_incomeBuffer;
			shared_ptr<HTTPRequest> m_request;
			shared_ptr<HTTPReply> m_reply;
			HTTPReplyParser m_parser;
			HTTPReplyHandler m_handler;
			HTTPRequestSerializer m_serializer;
			tcp::socket m_connectionSocket;

		private:
			void read();
			void write();

		public:
			ClientConection(tcp::socket connectionSocket, shared_ptr<HTTPRequest> request);

			void Run();
		};
	}
}

