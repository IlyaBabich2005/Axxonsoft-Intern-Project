#include "Client.hpp"

int main()
{
	AxxonsoftInternProject::Client::Client client{ AxxonsoftInternProject::Client::config::g_serverIP, AxxonsoftInternProject::Client::config::g_serverPort};

	client.Run();
}