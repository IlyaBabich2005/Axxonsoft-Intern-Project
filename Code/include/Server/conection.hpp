#pragma once

#include <array>

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/impl/write.hpp>

using	boost::asio::ip::tcp,
		boost::asio::buffer,
		boost::system::error_code,
		std::enable_shared_from_this,
		std::size_t,
		std::array;

namespace AxxonsoftInternProject
{
	namespace SERVER
	{
		class Conection : public enable_shared_from_this<Conection>
		{
		private:
			static const size_t bufferSize{ 1 * 1024 };
			array<char, Conection::bufferSize> incomeBuffer;
			tcp::socket connectionSocket;

		private:
			void Read();
			void Write();

		public:
			Conection(tcp::socket connectionSocket);

			void Run();
		};
	}
}