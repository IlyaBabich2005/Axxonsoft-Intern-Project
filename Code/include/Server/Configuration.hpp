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
			const std::string g_serverPort{ "3000" };
			const int g_threadPollSize{ 8 };
			const std::string g_adminPassword{ "admin" };
			const std::string g_adminUsername{ "admin" };
			const int g_sessionIdSize{ 64 };
			const int g_charSetSize{ 127 };
			const int g_lastSpecialChar{ 32 };
			const int g_sessionLifetimeInMinutes = 60;
		}
	}
}