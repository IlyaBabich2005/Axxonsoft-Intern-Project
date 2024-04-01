#include <iostream>

#include "server.hpp"

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

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