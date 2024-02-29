#include "conection.hpp"

namespace AxxonsoftInternProject
{
	namespace SERVER
	{
		void Conection::Read()
		{
			auto self(shared_from_this());
			this->connectionSocket.async_read_some(buffer(this->incomeBuffer),
				[self, this](error_code ec, size_t bytesTransferred)
				{
					std::cout << "Get " << bytesTransferred << " bytes \n";

					if (!ec)
					{
						ParsingStatus status = parcer.Parse(this->incomeBuffer.data(), this->incomeBuffer.data() + bytesTransferred);

						std::cout << "Parsed\n";

						if (status == ParsingStatus::endResultBad)
						{
							std::cout << "Parsed Bad\n";
						}
						else if (status == ParsingStatus::endResultGood)
						{
							std::cout << "Parsed GOOD\n";
							this->handler.Handle();
							std::cout << "Handling\n";
							this->Write();
						}
						else
						{
							std::cout << "Parsing Continue\n";
							this->Read();
						}
					}
				});
		}

		void Conection::Write()
		{
			std::cout << "Write\n";

			//vector<const_buffer> buffer_;
			//vector<const_buffer> buffer__;
			//buffer_.push_back(buffer("HTTP/1.0 200 OK"));
			//buffer__.push_back(buffer("\r\n\r\n"));
			//buffer_.insert(std::end(buffer_), std::begin(buffer__), std::end(buffer__));
			//

			auto self(shared_from_this());
			boost::asio::async_write(this->connectionSocket, this->reply->Serialize(),
				[this, self](error_code ec, std::size_t)
				{
					if (!ec)
					{
					}
				});
		}

		Conection::Conection(tcp::socket connectionSocket) :
			connectionSocket{ std::move(connectionSocket) },
			request{new HTTPRequest},
			reply{new HTTPReply},
			parcer{this->request},
			handler{this->request, this->reply}
		{
		}

		void Conection::Run()
		{
			this->Read();
		}
	}
}