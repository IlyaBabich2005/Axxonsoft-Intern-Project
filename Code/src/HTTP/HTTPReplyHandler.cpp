#include "HTTPReplyHandler.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		HTTPReplyHandler::HTTPReplyHandler(std::shared_ptr<HTTPReply> handledDocument, ClientRequestType requestType) :
			HTTPHandler { std::dynamic_pointer_cast<HTTPDocument>(handledDocument) },
			m_requestType { requestType }
		{
		}

		HTTPReplyHandler::~HTTPReplyHandler()
		{
		}

		void HTTPReplyHandler::downloadGettedFile()
		{
			nlohmann::json body = nlohmann::json::parse(handledDocument->body);

			std::vector<std::byte> bytes = body["data"];

			string pathToFile = { serverConfiguration::g_serverRootDirectory + string{body["filename"] } };

			std::ofstream file{ pathToFile, std::ios::binary | std::ios::trunc };

			if (file.is_open())
			{
				file.write((char*)bytes.data(), bytes.size());
			}

			file.close();
		}

		void HTTPReplyHandler::verifyVersion()
		{
			try
			{
				std::stod(handledDocument->version.substr(5));

				if (handledDocument->version.substr(0, 5) != "HTTP/")
				{
					throw new exceptions::InvalidHTTPVersionException{};
				}
			}
			catch (std::exception& ex)
			{
				std::cout << "Bad reply\n";
			}
		}

		void HTTPReplyHandler::handleBadRequest()
		{
			std::cout << "Bad request\n";
		}

		void HTTPReplyHandler::handleNotFound()
		{
			std::cout << "Not Found\n";
		}

		void HTTPReplyHandler::handleOk()
		{
			if (m_requestType == ClientRequestType::checkTarget)
			{
				nlohmann::json body = nlohmann::json::parse(handledDocument->body);

				try
				{
					std::vector<string> content = body["content"];

					for (auto target : content)
					{
						std::cout << target << "\n";
					}
				}
				catch (std::exception& ex)
				{
					std::cout << "empty\n";
				}
			}
			else if (m_requestType == ClientRequestType::downloadTarget)
			{
				downloadGettedFile();
				std::cout << "Target was successfully downloaded\n";
			}
			else if (m_requestType == ClientRequestType::deleteTarget)
			{
				std::cout << "Target was sucessfully deleted\n";
			}
			else if(m_requestType == ClientRequestType::sendTarget)
			{
				std::cout << "Target was sucessfully sended\n";
			}
			else
			{
				std::cout << "Client request type error\n";
			}
		}

		void HTTPReplyHandler::handleStatus()
		{
			std::shared_ptr<HTTPReply> handledReply = std::dynamic_pointer_cast<HTTPReply>(handledDocument);

			if (handledReply->status == stock::replyStatuses::g_badRequest)
			{
				handleBadRequest();
			}
			if (handledReply->status == stock::replyStatuses::g_notFound)
			{
				handleNotFound();
			}
			if (handledReply->status == stock::replyStatuses::g_ok)
			{
				handleOk();
			}                                                   
		}

		void HTTPReplyHandler::Handle()
		{
			try
			{
				this->verifyVersion();
				this->handleStatus();
			}
			catch(std::exception& ex)
			{
				std::cout << "Handling error\n";
			}
		}
	}
}