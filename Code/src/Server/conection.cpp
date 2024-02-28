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
					if (!ec)
					{
						//ParsingStatus status = parcer.Parse(this->incomeBuffer.data(), this->incomeBuffer.data() + bytesTransferred);

						/*if (status == ParsingStatus::endResultBad)
						{
							
						}
						else if (status == ParsingStatus::endResultGood)
						{
							//this->handler.Handle();
							this->Write();
						}
						else
						{
							this->Read();
						}*/
					}
				});
		}

		void Conection::Write()
		{
			auto self(shared_from_this());
			//boost::asio::async_write(this->connectionSocket, this->reply->Serialize(),
				//[this, self](error_code ec, std::size_t)
				//{
					//if (!ec)
					//{
					//}
				//});
		}

		Conection::Conection(tcp::socket connectionSocket) :
			connectionSocket{ std::move(connectionSocket) }
		{
		}

		void Conection::Run()
		{
			//this->Read();
		}
	}
}