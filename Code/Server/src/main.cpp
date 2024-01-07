#include <iostream>
#include <chrono>

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#include <boost/asio.hpp>

using namespace boost::asio;

int main()
{
	thread_pool pool{ 3 };

	boost::system::error_code ec;
	boost::asio::strand<boost::asio::thread_pool::executor_type> strand(pool.executor());
	boost::asio::strand<boost::asio::thread_pool::executor_type> strand2(pool.executor());
	boost::asio::steady_timer timer(strand, std::chrono::seconds{1});
	boost::asio::steady_timer timer2(strand2, std::chrono::seconds{ 1 });


	for (int i = 0; i < 100; i++)
	{
		timer.async_wait([i](boost::system::error_code ec) {std::cout << std::this_thread::get_id() << " " + std::to_string(i) + "\n"; });
		timer2.async_wait([i](boost::system::error_code ec) {std::cout << std::this_thread::get_id() << " 2 " + std::to_string(i) + "\n"; });
	}

	pool.join();
	
	return 0;
}