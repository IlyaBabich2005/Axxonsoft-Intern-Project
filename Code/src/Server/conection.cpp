#include "conection.hpp"

namespace AxxonsoftInternProject
{
	namespace SERVER
	{
		void Conection::read()
		{
			auto self(shared_from_this());
			m_connectionSocket.async_read_some(boost::asio::buffer(m_incomeBuffer),
				[self, this](boost::system::error_code ec, size_t bytesTransferred)
				{
					std::cout << boost::format("Get %1% bytes\n") % bytesTransferred;

					if (!ec)
					{
						http::ParsingStatus status = m_parcer.Parse(m_incomeBuffer.data(), m_incomeBuffer.data() + bytesTransferred);

						std::cout << AxxonsoftInternProject::http::stock::messages::g_parced << "\n";

						if (status == http::ParsingStatus::endResultBad)
						{
							std::cout << boost::format("%1%\n") % AxxonsoftInternProject::http::stock::messages::g_parcedBad;
							*m_reply = AxxonsoftInternProject::http::stock::replyes::g_badRequest;
						}
						else if (status == http::ParsingStatus::endResultGood)
						{
							std::cout << boost::format("%1%\n") % AxxonsoftInternProject::http::stock::messages::g_parcedGood;
							m_handler.Handle();
							std::cout << boost::format("%1%\n") % AxxonsoftInternProject::http::stock::messages::g_handling;
							write();
						}
						else
						{
							std::cout << boost::format("%1%\n") % AxxonsoftInternProject::http::stock::messages::g_parcingContinious;
							read();
						}
					}
				});
		}

		void Conection::write()
		{
			std::cout << boost::format("%1%\n") % AxxonsoftInternProject::http::stock::messages::g_writing;

			auto self(shared_from_this());
			async_write(m_connectionSocket, m_serializer.Serialize(m_reply),
				[this, self](boost::system::error_code ec, size_t)
				{
					if (!ec)
					{
						std::cout << boost::format("%1%\n") % AxxonsoftInternProject::http::stock::messages::g_written;
					}
				});
		}

		Conection::Conection(boost::asio::ip::tcp::socket connectionSocket, std::shared_ptr<SessionManager> sessionManager) :
			m_connectionSocket{ std::move(connectionSocket) },
			m_request{new http::HTTPRequest},
			m_reply{new http::HTTPReply},
			m_parcer{m_request},
			m_handler{m_request, m_reply, sessionManager}
		{
		}

		void Conection::Run()
		{
			read();
		}
	}
}