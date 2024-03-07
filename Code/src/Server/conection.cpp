#include "conection.hpp"

namespace AxxonsoftInternProject
{
	namespace SERVER
	{
		void Conection::read()
		{
			auto self(shared_from_this());
			m_connectionSocket.async_read_some(buffer(m_incomeBuffer),
				[self, this](error_code ec, size_t bytesTransferred)
				{
					cout << "Get " << bytesTransferred << " bytes \n";

					if (!ec)
					{
						ParsingStatus status = m_parcer.Parse(m_incomeBuffer.data(), m_incomeBuffer.data() + bytesTransferred);

						cout << "Parsed\n";

						if (status == ParsingStatus::endResultBad)
						{
							cout << "Parsed Bad\n";
							*m_reply = g_badRequest;
						}
						else if (status == ParsingStatus::endResultGood)
						{
							cout << "Parsed GOOD\n";
							m_handler.Handle();
							cout << "Handling\n";
							write();
						}
						else
						{
							cout << "Parsing Continue\n";
							read();
						}
					}
				});
		}

		void Conection::write()
		{
			cout << "Write\n";

			auto self(shared_from_this());
			async_write(m_connectionSocket, m_serializer.Serialize(m_reply),
				[this, self](error_code ec, size_t)
				{
					if (!ec)
					{
						cout << "Written!\n";
					}
				});
		}

		Conection::Conection(tcp::socket connectionSocket) :
			m_connectionSocket{ move(connectionSocket) },
			m_request{new HTTPRequest},
			m_reply{new HTTPReply},
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