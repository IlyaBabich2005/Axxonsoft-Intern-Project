#include "Client.hpp"

int main()
{
	AxxonsoftInternProject::Client::Client client{ "127.0.0.1", "80"};

	client.Run();
}