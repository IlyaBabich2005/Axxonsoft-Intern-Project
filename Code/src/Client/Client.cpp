#include "Client.hpp"

namespace AxxonsoftInternProject
{
	namespace Client
	{
		Client::Client(string serverIP, string serverPort) :
			connectionSocket{ this->context },
			handler { this->outputRequest },
			command{ new Command },
			outputRequest { new HTTPRequest }
		{
			tcp::resolver resolver{ this->context };
			this->serverEndpoint = *resolver.resolve(serverIP, serverPort).begin();
		}
	}

	void Client::Client::ReadCommand()
	{
		string command;

		this->command = shared_ptr<Command>{ new Command };

		std::getline(std::cin, command);
			
		if (parcer.Parce(this->command, command) == ParsingStatus::endResultGood)
		{
			this->handler.Handle(*this->command);
			this->Connect();
		}
		else
		{
			std::cout << "Bad command\n";
			this->ReadCommand();
		}

	}

	void Client::Client::Connect()
	{
		connectionSocket.async_connect(this->serverEndpoint,
			[this](error_code ec)
			{
				if (!ec)
				{
					std::make_shared<ClientConection>(std::move(connectionSocket), this->outputRequest)->Run();
				}
				else
				{
					std::cout << "Can't connect\n";
				}
			});
	}

	void Client::Client::Run()
	{
		this->ReadCommand();
		this->context.run();
	}
}