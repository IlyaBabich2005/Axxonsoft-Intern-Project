#include <iostream>
#include <chrono>

#include "server.hpp"

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#include "HTTPDocument.hpp"

int main()
{
	AxxonsoftInternProject::SERVER::Server server{
		AxxonsoftInternProject::SERVER::Configuration::g_serverAdress, 
		AxxonsoftInternProject::SERVER::Configuration::g_serverPort, 
		AxxonsoftInternProject::SERVER::Configuration::g_threadPollSize
	};
	server.Run();

	std::cin;
	
	return 0;
}