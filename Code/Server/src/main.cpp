#include <iostream>
#include <chrono>

#include "server.hpp"

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#include "HTTPDocument.hpp"


int main()
{
	AxxonsoftInternProject::SERVER::Server server{"127.0.0.1", "80", 8};
	server.Run();
	
	return 0;
}