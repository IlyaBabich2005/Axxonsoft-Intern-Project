#include "Client.hpp"

namespace AxxonsoftInternProject
{
	namespace Client
	{
		Client::Client(string serverIP, string serverPort) :
			m_connectionSocket{ m_context },
			m_handler { m_outputRequest },
			m_command{ new Command },
			m_outputRequest { new HTTPRequest }
		{
			tcp::resolver resolver{ m_context };
			m_serverEndpoint = *resolver.resolve(serverIP, serverPort).begin();
		}
	}

	void Client::Client::readCommand()
	{
		string command;

		m_command = shared_ptr<Command>{ new Command };

		getline(cin, command);
			
		if (m_parcer.Parce(m_command, command) == ParsingStatus::endResultGood)
		{
			m_handler.Handle(*m_command);
			connect();
		}
		else
		{
			std::cout << "Bad command\n";
			readCommand();
		}

	}

	void Client::Client::connect()
	{
		m_connectionSocket.async_connect(m_serverEndpoint,
			[this](error_code ec)
			{
				if (!ec)
				{
					make_shared<ClientConection>(move(m_connectionSocket), m_outputRequest)->Run();
				}
				else
				{
					cout << "Can't connect\n";
				}
			});
	}

	void Client::Client::Run()
	{
		readCommand();
		m_context.run();
	}
}