#include "ClientConnection.hpp"

namespace AxxonsoftInternProject
{
	namespace Client
	{
		ClientConection::ClientConection(boost::asio::ip::tcp::socket connectionSocket, std::shared_ptr<http::HTTPRequest> request) : 
			m_connectionSocket{ std::move(connectionSocket) },
			m_request{ request },
			m_reply{ new http::HTTPReply },
			m_parser{ m_reply },
			m_handler{ m_reply , request->m_type}
		{
		}

		void ClientConection::write()
		{
			std::cout << boost::format("%1%\n") % AxxonsoftInternProject::http::stock::messages::g_writing;

			auto self(shared_from_this());
			boost::asio::async_write(m_connectionSocket, m_serializer.Serialize(m_request),
				[this, self](boost::system::error_code ec, std::size_t)
				{
					if (!ec)
					{
						std::cout << boost::format("%1%\n") % AxxonsoftInternProject::http::stock::messages::g_written;
						read();
					}
				});
		}

		void ClientConection::read()
		{
			auto self(shared_from_this());
			m_connectionSocket.async_read_some(boost::asio::buffer(m_incomeBuffer),
				[self, this](boost::system::error_code ec, std::size_t bytesTransferred)
				{
					std::cout << boost::format("Get %1% bytes\n") % bytesTransferred;

					if (!ec)
					{
						http::ParsingStatus status = m_parser.Parse(m_incomeBuffer.data(), m_incomeBuffer.data() + bytesTransferred);

						std::cout << boost::format("%1%\n") % AxxonsoftInternProject::http::stock::messages::g_parced;

						if (status == http::ParsingStatus::endResultBad)
						{
							std::cout << boost::format("%1%\n") % AxxonsoftInternProject::http::stock::messages::g_parcedBad;
							std::cout << boost::format("%1%\n") % AxxonsoftInternProject::http::stock::messages::g_badReply;
						}
						else if (status == http::ParsingStatus::endResultGood)
						{
							std::cout << boost::format("%1%\n") % AxxonsoftInternProject::http::stock::messages::g_parcedGood;
							m_handler.Handle();
						}
						else
						{
							std::cout << boost::format("%1%\n") % AxxonsoftInternProject::http::stock::messages::g_parcingContinious;
							read();
						}
					}
				});
		}

		void ClientConection::Run()
		{
			write();
		}
	}
}