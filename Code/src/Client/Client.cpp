#include "Client.hpp"

namespace AxxonsoftInternProject
{
	namespace Client
	{
		Client::Client(std::string serverIP, std::string serverPort) :
			m_connectionSocket{ m_context },
			m_handler { m_outputRequest },
			m_command{ new Command },
			m_outputRequest { new http::HTTPRequest }
		{
			boost::asio::ip::tcp::resolver resolver{ m_context };
			m_serverEndpoint = *resolver.resolve(serverIP, serverPort).begin();
		}
	}

	void Client::Client::readCommand()
	{
		std::string command;

		m_command = std::shared_ptr<Command>{ new Command };

		std::getline(std::cin, command);
			
		if (m_parcer.Parce(m_command, command) == http::ParsingStatus::endResultGood)
		{
			m_handler.Handle(*m_command);
			connect();
		}
		else
		{
			std::cout << AxxonsoftInternProject::http::stock::messages::g_badCommand << "\n";
			readCommand();
		}

	}

	void Client::Client::connect()
	{
		m_connectionSocket.async_connect(m_serverEndpoint,
			[this](boost::system::error_code ec)
			{
				if (!ec)
				{
					std::make_shared<ClientConection>(std::move(m_connectionSocket), m_outputRequest)->Run();
				}
				else
				{
					std::cout << AxxonsoftInternProject::http::stock::messages::g_cantConnect << "\n";
				}
			});
	}

	void Client::Client::Run()
	{
		readCommand();
		m_context.run();
	}
}