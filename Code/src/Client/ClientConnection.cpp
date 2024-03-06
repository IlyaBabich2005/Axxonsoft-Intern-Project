#include "ClientConnection.hpp"

namespace AxxonsoftInternProject
{
	namespace Client
	{
		ClientConection::ClientConection(tcp::socket connectionSocket, shared_ptr<HTTPRequest> request) : 
			connectionSocket{ std::move(connectionSocket) },
			request{ request },
			reply{ new HTTPReply },
			parser{ this->reply },
			handler{ this->reply , this->request->type}
		{
		}

		void ClientConection::Write()
		{
			std::cout << "Write\n";

			auto self(shared_from_this());
			boost::asio::async_write(this->connectionSocket, this->serializer.Serialize(this->request),
				[this, self](error_code ec, std::size_t)
				{
					if (!ec)
					{
						std::cout << "Written!\n";
						this->Read();
					}
				});
		}

		void ClientConection::Read()
		{
			auto self(shared_from_this());
			this->connectionSocket.async_read_some(buffer(this->incomeBuffer),
				[self, this](error_code ec, size_t bytesTransferred)
				{
					std::cout << "Get " << bytesTransferred << " bytes \n";

					if (!ec)
					{
						ParsingStatus status = parser.Parse(this->incomeBuffer.data(), this->incomeBuffer.data() + bytesTransferred);

						std::cout << "Parsed\n";

						if (status == ParsingStatus::endResultBad)
						{
							std::cout << "Parsed Bad\n";
							std::cout << "Bad Reply\n";
						}
						else if (status == ParsingStatus::endResultGood)
						{
							std::cout << "Parsed GOOD\n";
							this->handler.Handle();
						}
						else
						{
							std::cout << "Parsing Continue\n";
							this->Read();
						}
					}
				});
		}

		void ClientConection::Run()
		{
			this->Write();
		}
	}
}