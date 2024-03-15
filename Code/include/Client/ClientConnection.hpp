#pragma once

#include <array>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/impl/write.hpp>
#include <boost/format.hpp>

#include "HTTPReplyParser.hpp"
#include "HTTPReplyHandler.hpp"
#include "HTTPRequestSerializer.hpp"
#include "HTTPReply.hpp"

namespace AxxonsoftInternProject
{
	namespace Client
	{
		class ClientConection : public std::enable_shared_from_this<ClientConection>
		{
		private:
			static const std::size_t m_bufferSize{ 10 * 1024 };
			std::array<char, ClientConection::m_bufferSize> m_incomeBuffer;
			std::shared_ptr<AxxonsoftInternProject::http::HTTPRequest> m_request;
			std::shared_ptr<http::HTTPReply> m_reply;
			AxxonsoftInternProject::http::HTTPReplyParser m_parser;
			AxxonsoftInternProject::http::HTTPReplyHandler m_handler;
			AxxonsoftInternProject::http::HTTPRequestSerializer m_serializer;
			boost::asio::ip::tcp::socket m_connectionSocket;

		private:
			void read();
			void write();

		public:
			ClientConection(boost::asio::ip::tcp::socket connectionSocket, std::shared_ptr<AxxonsoftInternProject::http::HTTPRequest> request);

			void Run();
		};
	}
}

