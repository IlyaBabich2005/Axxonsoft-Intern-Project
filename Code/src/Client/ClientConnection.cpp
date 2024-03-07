#include "ClientConnection.hpp"

namespace AxxonsoftInternProject
{
	namespace Client
	{
		ClientConection::ClientConection(tcp::socket connectionSocket, shared_ptr<HTTPRequest> request) : 
			m_connectionSocket{ move(connectionSocket) },
			m_request{ request },
			m_reply{ new HTTPReply },
			m_parser{ m_reply },
			m_handler{ m_reply , request->type}
		{
		}

		void ClientConection::write()
		{
			cout << "Write\n";

			auto self(shared_from_this());
			async_write(m_connectionSocket, m_serializer.Serialize(m_request),
				[this, self](error_code ec, size_t)
				{
					if (!ec)
					{
						cout << "Written!\n";
						read();
					}
				});
		}

		void ClientConection::read()
		{
			auto self(shared_from_this());
			m_connectionSocket.async_read_some(buffer(m_incomeBuffer),
				[self, this](error_code ec, size_t bytesTransferred)
				{
					cout << "Get " << bytesTransferred << " bytes \n";

					if (!ec)
					{
						ParsingStatus status = m_parser.Parse(m_incomeBuffer.data(), m_incomeBuffer.data() + bytesTransferred);

						cout << "Parsed\n";

						if (status == ParsingStatus::endResultBad)
						{
							cout << "Parsed Bad\n";
							cout << "Bad Reply\n";
						}
						else if (status == ParsingStatus::endResultGood)
						{
							cout << "Parsed GOOD\n";
							m_handler.Handle();
						}
						else
						{
							cout << "Parsing Continue\n";
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