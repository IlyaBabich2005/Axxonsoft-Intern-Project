#include "HTTPReplyHandler.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		HTTPReplyHandler::HTTPReplyHandler
		(
			std::shared_ptr<HTTPReply> handledDocument,
			ClientRequestType requestType,
			std::shared_ptr<AxxonsoftInternProject::Client::LoginManager> loginManager
		) :
			HTTPHandler{ std::dynamic_pointer_cast<HTTPDocument>(handledDocument) },
			m_requestType{ requestType },
			m_loginManager{ loginManager }
		{
		}

		HTTPReplyHandler::HTTPReplyHandler()
		{
		}

		HTTPReplyHandler::~HTTPReplyHandler()
		{
		}

		void HTTPReplyHandler::downloadGettedFile()
		{
			nlohmann::json body = nlohmann::json::parse(m_handledDocument->m_body);

			std::vector<std::byte> bytes = body[stock::json::g_dataFieldName];

			std::string pathToFile = { AxxonsoftInternProject::SERVER::Configuration::g_serverRootDirectory +
				std::string{body[stock::json::g_filenameFiledName] } };

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
				if (m_handledDocument->m_version == version)
				{
					return;
				}
			}

			throw new exceptions::InvalidHTTPVersionException{};
		}

		void HTTPReplyHandler::handleBadRequest()
		{
			std::cout << boost::format("%1%\n") % stock::messages::g_badRequest;
		}

		void HTTPReplyHandler::handleNotFound()
		{
			std::cout << boost::format("%1%\n") % stock::messages::g_notFound;
		}

		void HTTPReplyHandler::handleOk()
		{
			if (m_requestType == ClientRequestType::checkTarget)
			{
				showFolderContent();
			}
			else if (m_requestType == ClientRequestType::downloadTarget)
			{
				downloadGettedFile();
				std::cout << boost::format("%1%\n") % stock::messages::g_targetWasSuccesfullyDownloaded;
			}
			else if (m_requestType == ClientRequestType::deleteTarget)
			{
				std::cout << boost::format("%1%\n") % stock::messages::g_targetWasSuccesfullyDeleted;
			}
			else if (m_requestType == ClientRequestType::sendTarget)
			{
				std::cout << boost::format("%1%\n") % stock::messages::g_targetWasSuccesfullySended;
			}
			else
			{
				std::cout << boost::format("%1%\n") % stock::messages::g_clientRequestTypeError;
			}
		}

		void HTTPReplyHandler::handleUnauthorized()
		{
			for (auto header : m_handledDocument->m_headers)
			{
				m_loginManager->m_isNeedToLogin = true;

				if (header.m_name == stock::headers::names::g_wwwAuthenticate)
				{
					handleAuthHeader(header);
					std::cout << boost::format("%1%\n") % stock::messages::g_unauthorized;

					std::cout << boost::format("%1%\n") % AxxonsoftInternProject::http::stock::messages::g_inputLogin;
					std::getline(std::cin, m_loginManager->m_login);
					std::cout << boost::format("%1%\n") % AxxonsoftInternProject::http::stock::messages::g_inputPassword;
					std::getline(std::cin, m_loginManager->m_password);

					return;
				}
			}
;
			std::cout << boost::format("%1%\n") % stock::messages::g_authError;
		}

		void HTTPReplyHandler::handleAuthHeader(const HTTPHeader& header)
		{
			for (auto field : header.m_classes.back().m_fields)
			{
				if (field.m_name == stock::headers::values::g_nonce)
				{
					m_loginManager->m_nonce = field.m_arguments.back().m_value;
				}
				else if (field.m_name == stock::headers::values::g_opaque)
				{
					m_loginManager->m_opaque = field.m_arguments.back().m_value;
				}
				else if (field.m_name == stock::headers::values::g_qop)
				{
					if (field.m_arguments.back().m_value == stock::headers::values::g_auth)
					{
						m_loginManager->m_qop = stock::headers::values::g_auth;
					}
				}
				else
				{
					std::cout << boost::format("%1%\n") % stock::messages::g_authError;
					m_loginManager->m_isNeedToLogin = false;
				}
			}
		}

		void HTTPReplyHandler::handleStatus()
		{
			std::shared_ptr<HTTPReply> handledReply = std::dynamic_pointer_cast<HTTPReply>(m_handledDocument);

			if (handledReply->m_status == stock::replyStatuses::g_badRequest)
			{
				handleBadRequest();
			}
			else if (handledReply->m_status == stock::replyStatuses::g_notFound)
			{
				handleNotFound();
			}
			else if (handledReply->m_status == stock::replyStatuses::g_ok)
			{
				handleOk();
			}                   
			else if (handledReply->m_status == stock::replyStatuses::g_unauthorized)
			{
				handleUnauthorized();
				return;
			}

			m_loginManager->m_isNeedToLogin = false;
		}

		void HTTPReplyHandler::showFolderContent()
		{
			nlohmann::json body = nlohmann::json::parse(m_handledDocument->m_body);

			try
			{
				std::vector<std::string> content = body[stock::json::g_contentFieldName];

				for (auto target : content)
				{
					std::cout << boost::format("%1%\n") % target;
				}
			}
			catch (std::exception& ex)
			{
				std::cout << boost::format("%1%\n") % ex.what();
			}
			catch (boost::exception& ex)
			{
				std::cout << boost::format("%1%\n") % boost::diagnostic_information(ex);
			}
		}

		void HTTPReplyHandler::Handle()
		{
			try
			{
				verifyVersion();
				handleStatus();
			}
			catch(std::exception& ex)
			{
				std::cout << boost::format("%1%\n") % ex.what();
			}
			catch (boost::exception& ex)
			{
				std::cout << boost::format("%1%\n") % boost::diagnostic_information(ex);
			}
		}
	}
}