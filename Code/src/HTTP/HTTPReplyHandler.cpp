#include "HTTPReplyHandler.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		HTTPReplyHandler::HTTPReplyHandler(shared_ptr<HTTPReply> handledDocument, ClientRequestType requestType) :
			HTTPHandler { dynamic_pointer_cast<HTTPDocument>(handledDocument) },
			m_requestType { requestType }
		{
		}

		HTTPReplyHandler::~HTTPReplyHandler()
		{
		}

		void HTTPReplyHandler::downloadGettedFile()
		{
			json body = json::parse(handledDocument->body);

			vector<byte> bytes = body["data"];

			string pathToFile = { g_serverRootDirectory + string{body["filename"] } };

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
				stod(handledDocument->version.substr(5));

				if (handledDocument->version.substr(0, 5) != "HTTP/")
				{
					throw new InvalidHTTPVersionException{};
				}
			}
			catch (exception& ex)
			{
				cout << "Bad reply\n";
			}
		}

		void HTTPReplyHandler::handleBadRequest()
		{
			cout << "Bad request\n";
		}

		void HTTPReplyHandler::handleNotFound()
		{
			cout << "Not Found\n";
		}

		void HTTPReplyHandler::handleOk()
		{
			if (m_requestType == ClientRequestType::checkTarget)
			{
				json body = json::parse(handledDocument->body);

				try
				{
					vector<string> content = body["content"];

					for (auto target : content)
					{
						cout << target << "\n";
					}
				}
				catch (exception& ex)
				{
					cout << "empty\n";
				}
			}
			else if (m_requestType == ClientRequestType::downloadTarget)
			{
				downloadGettedFile();
				cout << "Target was successfully downloaded\n";
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
			shared_ptr<HTTPReply> handledReply = dynamic_pointer_cast<HTTPReply>(handledDocument);

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
			catch(exception& ex)
			{
				cout << "Handling error\n";
			}
		}
	}
}