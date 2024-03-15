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
					showBytesGetted(bytesTransferred);

					if (!ec)
					{
						http::ParsingStatus status = m_parcer.Parse(m_incomeBuffer.data(), m_incomeBuffer.data() + bytesTransferred);

						std::cout << AxxonsoftInternProject::http::stock::messages::g_parced << "\n";

						if (status == http::ParsingStatus::endResultBad)
						{
							std::cout << AxxonsoftInternProject::http::stock::messages::g_parcedBad << "\n";
							*m_reply = AxxonsoftInternProject::http::stock::replyes::g_badRequest;
						}
						else if (status == http::ParsingStatus::endResultGood)
						{
							std::cout << AxxonsoftInternProject::http::stock::messages::g_parcedGood << "\n";
							m_handler.Handle();
							std::cout << AxxonsoftInternProject::http::stock::messages::g_handling << "\n";
							write();
						}
						else
						{
							std::cout << AxxonsoftInternProject::http::stock::messages::g_parcingContinious << "\n";
							read();
						}
					}
				});
		}

		void Conection::write()
		{
			std::cout << AxxonsoftInternProject::http::stock::messages::g_writing << "\n";

			auto self(shared_from_this());
			async_write(m_connectionSocket, m_serializer.Serialize(m_reply),
				[this, self](boost::system::error_code ec, size_t)
				{
					if (!ec)
					{
						std::cout << AxxonsoftInternProject::http::stock::messages::g_written << "\n";
					}
				});
		}


		std::string Conection::showBytesGetted(std::size_t bytesTransferred)
		{
			std::cout << "Get " << bytesTransferred << " bytes \n";
		}

		Conection::Conection(boost::asio::ip::tcp::socket connectionSocket) :
			m_connectionSocket{ std::move(connectionSocket) },
			m_request{new http::HTTPRequest},
			m_reply{new http::HTTPReply},
			m_parcer{m_request},
			m_handler{m_request, m_reply}
		{
		}

		void Conection::Run()
		{
			read();
		}
	}
}