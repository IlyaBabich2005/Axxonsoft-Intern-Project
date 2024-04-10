#include "Client.hpp"

namespace AxxonsoftInternProject
{
	namespace Client
	{
		Client::Client(std::string serverIP, std::string serverPort, boost::asio::io_context& context) :
			m_connectionSocket{ context },
			m_request{ new http::HTTPRequest },
			m_reply{ new http::HTTPReply },
			m_command{ new Command },
			m_replyParcer{m_reply},
			m_loginManager{ new LoginManager }
		{
			m_commandHandler = CommandHandler{ m_loginManager };
			boost::asio::ip::tcp::resolver resolver{ context };
			m_serverEndpoint = *resolver.resolve(serverIP, serverPort).begin();
		}
	}

	void Client::Client::readCommand()
	{
		m_command = std::shared_ptr<Command>{ new Command };
		std::cout << boost::format("%1%\n") % AxxonsoftInternProject::http::stock::messages::g_inputCommand;
		std::getline(std::cin, m_oldCommand);
		
		m_request = std::shared_ptr<http::HTTPRequest>{ new http::HTTPRequest };

		if (m_commandParcer.Parce(m_command, m_oldCommand) == http::ParsingStatus::endResultGood)
		{
			if (m_commandHandler.Handle(*m_command, m_request) == HandlingResult::Success)
			{
				m_replyHandler = http::HTTPReplyHandler{ m_reply, m_request->m_type, m_loginManager};
				writeRequest();
			}
			else
			{
				return;
			}	
		}
		else
		{
			std::cout << boost::format("%1%\n") % AxxonsoftInternProject::http::stock::messages::g_badCommand;
		}
	}

	void Client::Client::connect()
	{
		try
		{
			m_connectionSocket.connect(m_serverEndpoint);
		}
		catch (std::exception& ex)
		{
			std::cout << boost::format("%1%\n") % ex.what();
		}
		catch (boost::exception& ex)
		{
			std::cout << boost::format("%1%\n") % boost::diagnostic_information(ex);
		}
	}

	void Client::Client::writeRequest()
	{
		std::cout << boost::format("%1%\n") % AxxonsoftInternProject::http::stock::messages::g_writing;

		try
		{
			boost::asio::write(m_connectionSocket, m_serializer.Serialize(m_request));

			std::cout << boost::format("%1%\n") % AxxonsoftInternProject::http::stock::messages::g_written;
			*m_reply = http::HTTPReply{};
			readReply();
		}
		catch (std::exception& ex)
		{
			std::cout << boost::format("%1%\n") % ex.what();
		}
		catch (boost::exception& ex)
		{
			std::cout << boost::format("%1%\n") % boost::diagnostic_information(ex);
		}
	}

	void Client::Client::readReply()
	{
		try 
		{
			std::size_t bytesTransferred = m_connectionSocket.read_some(boost::asio::buffer(m_incomeBuffer));

			std::cout << boost::format("Get %1% bytes\n") % bytesTransferred;

			http::ParsingStatus status = m_replyParcer.Parse(m_incomeBuffer.data(), m_incomeBuffer.data() + bytesTransferred);

			std::cout << boost::format("%1%\n") % AxxonsoftInternProject::http::stock::messages::g_parced;

			if (status == http::ParsingStatus::endResultBad)
			{
				std::cout << boost::format("%1%\n") % AxxonsoftInternProject::http::stock::messages::g_parcedBad;
				std::cout << boost::format("%1%\n") % AxxonsoftInternProject::http::stock::messages::g_badReply;
			}
			else if (status == http::ParsingStatus::endResultGood)
			{
				std::cout << boost::format("%1%\n") % AxxonsoftInternProject::http::stock::messages::g_parcedGood;
				m_replyHandler.Handle();
			}
			else
			{
				std::cout << boost::format("%1%\n") % AxxonsoftInternProject::http::stock::messages::g_parcingContinious;
				readReply();
			}
		}
		catch (std::exception& ex)
		{
			std::cout << boost::format("%1%\n") % ex.what();
		}
		catch (boost::exception& ex)
		{
			std::cout << boost::format("%1%\n") % boost::diagnostic_information(ex);
		}
	}

	void Client::Client::Run()
	{
		connect();
		readCommand();
		m_connectionSocket.close();
	}
}