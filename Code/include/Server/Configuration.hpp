#pragma once

#include <string>

namespace AxxonsoftInternProject
{
	namespace SERVER
	{
		namespace Configuration
		{
			const std::string g_httpVersion{ "HTTP/1.0" };
			const std::string g_serverRootDirectory{ "./files/" };
			const std::string g_serverAdress{ "127.0.0.1" };
			const std::string g_serverPort{ "80" };
			const int g_threadPollSize{ 8 };
		}
	}
}