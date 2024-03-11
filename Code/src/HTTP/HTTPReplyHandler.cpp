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
			nlohmann::json body = nlohmann::json::parse(m_handledDocument->body);

			std::vector<std::byte> bytes = body[stock::json::g_dataFieldName];

			string pathToFile = { serverConfiguration::g_serverRootDirectory + string{body[stock::json::g_filenameFiledName] } };

			std::ofstream file{ pathToFile, std::ios::binary | std::ios::trunc };

			if (file.is_open())
			{
				file.write((char*)bytes.data(), bytes.size());
			}

			file.close();
		}

		void HTTPReplyHandler::verifyVersion()
		{
			for (auto version : stock::g_httpVersions)
			{
				if (this->m_handledDocument->version == version)
				{
					return;
				}
			}

			throw new exceptions::InvalidHTTPVersionException{};
		}

		void HTTPReplyHandler::handleBadRequest()
		{
			std::cout << stock::messages::g_badRequest << "\n";
		}

		void HTTPReplyHandler::handleNotFound()
		{
			std::cout << stock::messages::g_notFound << "\n";
		}

		void HTTPReplyHandler::handleOk()
		{
			if (m_requestType == ClientRequestType::checkTarget)
			{
				nlohmann::json body = nlohmann::json::parse(m_handledDocument->body);

				try
				{
					std::vector<string> content = body[stock::json::g_contentFieldName];

					for (auto target : content)
					{
						std::cout << target << "\n";
					}
				}
				catch (std::exception& ex)
				{
					std::cout << ex.what() << "\n";
				}
				catch (boost::exception& ex)
				{
					std::cout << boost::diagnostic_information(ex) << "\n";
				}
			}
			else if (m_requestType == ClientRequestType::downloadTarget)
			{
				downloadGettedFile();
				std::cout << stock::messages::g_targetWasSuccesfullyDownloaded << "\n";
			}
			else if (m_requestType == ClientRequestType::deleteTarget)
			{
				std::cout << stock::messages::g_targetWasSuccesfullyDeleted << "\n";
			}
			else if(m_requestType == ClientRequestType::sendTarget)
			{
				std::cout << stock::messages::g_targetWasSuccesfullySended << "\n";
			}
			else
			{
				std::cout << stock::messages::g_clientRequestTypeError << "\n";
			}
		}

		void HTTPReplyHandler::handleStatus()
		{
			std::shared_ptr<HTTPReply> handledReply = std::dynamic_pointer_cast<HTTPReply>(m_handledDocument);

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
				std::cout << ex.what() << "\n";
			}
			catch (boost::exception& ex)
			{
				std::cout << boost::diagnostic_information(ex) << "\n";
			}
		}
	}
}