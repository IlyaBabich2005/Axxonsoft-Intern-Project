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

using	boost::asio::ip::tcp,
		boost::asio::buffer,
		boost::asio::async_write,
		boost::system::error_code,
		http::HTTPRequestParcer,
		http::HTTPRequestHandler,
		http::HTTPRequest,
		http::HTTPReply,
		http::ParsingStatus,
		http::HTTPReplySerializer,
		std::enable_shared_from_this,
		std::size_t,
		std::cout,
		std::array,
		std::move,
		stock::replyes::g_badRequest;

namespace AxxonsoftInternProject
{
	namespace SERVER
	{
		class Conection : public enable_shared_from_this<Conection>
		{
		private:
			static const size_t m_bufferSize{ 10 * 1024};
			array<char, Conection::m_bufferSize> m_incomeBuffer;
			shared_ptr<HTTPRequest> m_request;
			shared_ptr<HTTPReply> m_reply;
			HTTPRequestParcer m_parcer;
			HTTPRequestHandler m_handler;
			HTTPReplySerializer m_serializer;
			tcp::socket m_connectionSocket;

		private:
			void read();
			void write();

		public:
			Conection(tcp::socket connectionSocket);

			void Run();
		};
	}
}
