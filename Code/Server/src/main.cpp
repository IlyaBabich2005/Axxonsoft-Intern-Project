#include <iostream>
#include <chrono>

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#include <boost/asio.hpp>

int main()
{
	boost::asio::io_context context;
	boost::system::error_code ec;
	boost::asio::steady_timer timer(context, std::chrono::seconds{0});

	timer.async_wait([&](boost::system::error_code ec) {std::cout << "5 seconds left"; });

	std::cout << "test\n";

	context.run();
	
	return 0;
}