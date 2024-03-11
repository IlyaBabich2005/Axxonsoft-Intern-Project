#include "ClientConnection.hpp"

namespace AxxonsoftInternProject
{
	namespace Client
	{
		ClientConection::ClientConection(ip::tcp::socket connectionSocket, std::shared_ptr<http::HTTPRequest> request) : 
			m_connectionSocket{ std::move(connectionSocket) },
			m_request{ request },
			m_reply{ new http::HTTPReply },
			m_parser{ m_reply },
			m_handler{ m_reply , request->type}
		{
		}

		void ClientConection::write()
		{
			std::cout << stock::messages::g_writing << '\n';

			auto self(shared_from_this());
			asio::async_write(m_connectionSocket, m_serializer.Serialize(m_request),
				[this, self](system::error_code ec, std::size_t)
				{
					if (!ec)
					{
						std::cout << stock::messages::g_written << "\n";
						read();
					}
				});
		}

		std::string ClientConection::showBytesGetted(std::size_t bytesTransferred)
		{
			std::cout << "Get " << bytesTransferred << " bytes \n";
		}

		void ClientConection::read()
		{
			auto self(shared_from_this());
			m_connectionSocket.async_read_some(asio::buffer(m_incomeBuffer),
				[self, this](system::error_code ec, std::size_t bytesTransferred)
				{
					showBytesGetted(bytesTransferred);

					if (!ec)
					{
						http::ParsingStatus status = m_parser.Parse(m_incomeBuffer.data(), m_incomeBuffer.data() + bytesTransferred);

						std::cout << stock::messages::g_parced << "\n";

						if (status == http::ParsingStatus::endResultBad)
						{
							std::cout << stock::messages::g_parcedBad << "\n";
							std::cout << stock::messages::g_badReply << "\n";
						}
						else if (status == http::ParsingStatus::endResultGood)
						{
							std::cout << stock::messages::g_parcedGood << "\n";
							m_handler.Handle();
						}
						else
						{
							std::cout << stock::messages::g_parcingContinious << "\n";
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