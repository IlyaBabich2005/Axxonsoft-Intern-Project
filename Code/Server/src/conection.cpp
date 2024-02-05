#include "conection.hpp"

namespace AxxonsoftInternProject
{
	namespace SERVER
	{
		void Conection::Read()
		{
			this->connectionSocket.async_read_some(buffer(textBuffer),
				[this](error_code ec, size_t bytesTransferred)
				{
					if (!ec)
					{
						this->Read();
					}
				});
		}

		void Conection::Write()
		{
		}

		Conection::Conection(tcp::socket connectionSocket) :
			connectionSocket{ std::move(connectionSocket) }
		{
		}

		void Conection::Run()
		{
			this->Read();
		}

		Conection::~Conection()
		{
		}
	}
}