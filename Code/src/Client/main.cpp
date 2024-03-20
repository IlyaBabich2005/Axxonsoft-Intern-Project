#include "Client.hpp"

int main()
{

	boost::asio::io_context context;

	AxxonsoftInternProject::Client::Client client{ 
		AxxonsoftInternProject::Client::config::g_serverIP, 
		AxxonsoftInternProject::Client::config::g_serverPort, 
		context};

	while (true)
	{
		client.Run();
		context.run();
	}
}