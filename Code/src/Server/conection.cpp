#include "conection.hpp"

namespace AxxonsoftInternProject
{
	namespace SERVER
	{
		void Conection::read()
		{
			auto self(shared_from_this());
			m_connectionSocket.async_read_some(asio::buffer(m_incomeBuffer),
				[self, this](system::error_code ec, size_t bytesTransferred)
				{
					std::cout << "Get " << bytesTransferred << " bytes \n";

					if (!ec)
					{
						http::ParsingStatus status = m_parcer.Parse(m_incomeBuffer.data(), m_incomeBuffer.data() + bytesTransferred);

						std::cout << "Parsed\n";

						if (status == http::ParsingStatus::endResultBad)
						{
							std::cout << "Parsed Bad\n";
							*m_reply = stock::replyes::g_badRequest;
						}
						else if (status == http::ParsingStatus::endResultGood)
						{
							std::cout << "Parsed GOOD\n";
							m_handler.Handle();
							std::cout << "Handling\n";
							write();
						}
						else
						{
							std::cout << "Parsing Continue\n";
							read();
						}
					}
				});
		}

		void Conection::write()
		{
			std::cout << "Write\n";

			auto self(shared_from_this());
			async_write(m_connectionSocket, m_serializer.Serialize(m_reply),
				[this, self](system::error_code ec, size_t)
				{
					if (!ec)
					{
						std::cout << "Written!\n";
					}
				});
		}

		Conection::Conection(ip::tcp::socket connectionSocket) :
			m_connectionSocket{ std::move(connectionSocket) },
			m_request{new http::HTTPRequest},
			m_reply{new http::HTTPReply},
			m_parcer{m_request},
			m_handler{m_request, m_reply}
		{
		}

		void Conection::Run()
		{
			this->read();
		}
	}
}