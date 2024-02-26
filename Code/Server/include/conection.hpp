#pragma once

#include <array>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/system/error_code.hpp>

#include "HTTPRequestParser.hpp"
#include "HTTPRequestHandler.hpp"
#include "HTTPRequest.hpp"
#include "HTTPReply"

namespace http = AxxonsoftInternProject::http;

using	boost::asio::ip::tcp,
		boost::asio::buffer,
		boost::system::error_code,
		http::HTTPRequestParcer,
		http::ParsingStatus,
		http::HTTPRequestHandler,
		http::HTTPReply,
		http::HTTPRequest,
		std::size_t,
		std::array;

namespace AxxonsoftInternProject
{
	namespace SERVER
	{
		class Conection
		{
		private:
			static const size_t bufferSize{ 1 * 1024 };
			array<char, Conection::bufferSize> textBuffer;
			tcp::socket connectionSocket;
			shared_ptr<HTTPRequest> request;
			shared_ptr<HTTPReply> reply;
			HTTPRequestParcer parcer;
			HTTPRequestHandler handler;

		private:
			void Read();
			void Write();

		public:
			Conection(tcp::socket connectionSocket);

			void Run();

			virtual ~Conection();
		};
	}
}
