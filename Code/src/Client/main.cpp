#include "Client.hpp"

int main()
{
	AxxonsoftInternProject::Client::Client client{ Client::config::g_serverIP, Client::config::g_serverPort};

	client.Run();
}