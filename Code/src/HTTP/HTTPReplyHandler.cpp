#include "HTTPReplyHandler.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		HTTPReplyHandler::HTTPReplyHandler(shared_ptr<HTTPReply> handledDocument, ClientRequestType requestType) :
			HTTPHandler { dynamic_pointer_cast<HTTPDocument>(handledDocument) },
			requestType { requestType }
		{
		}

		HTTPReplyHandler::~HTTPReplyHandler()
		{
		}

		void HTTPReplyHandler::DownloadGettedFile()
		{
			json body = json::parse(this->handledDocument->body);

			vector<std::byte> bytes = body["data"];

			string pathToFile = { "./files/" + string{body["filename"] } };

			std::ofstream file{ pathToFile, std::ios::binary | std::ios::trunc };

			if (file.is_open())
			{
				file.write((char*)bytes.data(), bytes.size());
			}

			file.close();
		}

		void HTTPReplyHandler::VerifyVersion()
		{
			try
			{
				std::stod(this->handledDocument->version.substr(5));

				if (this->handledDocument->version.substr(0, 5) != "HTTP/")
				{
					throw new InvalidHTTPVersionException{};
				}
			}
			catch (...)
			{
				std::cout << "Bad reply\n";
			}
		}

		void HTTPReplyHandler::HandleBadRequest()
		{
			std::cout << "Bad request\n";
		}

		void HTTPReplyHandler::HandleNotFound()
		{
			std::cout << "Not Found\n";
		}

		void HTTPReplyHandler::HandleOk()
		{
			if (this->requestType == ClientRequestType::checkTarget)
			{
				json body = json::parse(this->handledDocument->body);

				try
				{
					vector<string> content = body["content"];

					for (auto target : content)
					{
						std::cout << target << "\n";
					}
				}
				catch (...)
				{
					std::cout << "empty\n";
				}
			}
			else if (this->requestType == ClientRequestType::downloadTarget)
			{
				this->DownloadGettedFile();
				std::cout << "Target was successfully downloaded\n";
			}
			else if (this->requestType == ClientRequestType::deleteTarget)
			{
				std::cout << "Target was sucessfully deleted\n";
			}
			else if(this->requestType == ClientRequestType::sendTarget)
			{
				std::cout << "Target was sucessfully sended\n";
			}
			else
			{
				std::cout << "Client request type error\n";
			}
		}

		void HTTPReplyHandler::HandleStatus()
		{
			if (dynamic_pointer_cast<HTTPReply>(this->handledDocument)->status == stock::replyStatuses::badRequest)
			{
				HandleBadRequest();
			}
			if (dynamic_pointer_cast<HTTPReply>(this->handledDocument)->status == stock::replyStatuses::notFound)
			{
				HandleNotFound();
			}
			if (dynamic_pointer_cast<HTTPReply>(this->handledDocument)->status == stock::replyStatuses::ok)
			{
				HandleOk();
			}                                                   
		}

		void HTTPReplyHandler::Handle()
		{
			try
			{
				this->VerifyVersion();
				this->HandleStatus();
			}
			catch(...)
			{
				std::cout << "Handling error\n";
			}
		}
	}
}