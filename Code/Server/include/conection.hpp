#pragma once

#include <array>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/system/error_code.hpp>

using	boost::asio::ip::tcp,
		boost::asio::buffer,
		boost::system::error_code,
		std::size_t,
		std::array;

class Conection
{
private:
	static const size_t bufferSize{ 1 * 1024 };
	array<char, Conection::bufferSize> textBuffer;
	tcp::socket connectionSocket;


private:
	void Read();
	void Write();

public: 
	Conection(tcp::socket connectionSocket);

	void Run();

	virtual ~Conection();
};