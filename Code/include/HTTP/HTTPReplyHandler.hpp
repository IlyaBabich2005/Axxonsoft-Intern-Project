#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

#include <boost/exception/exception.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/format.hpp>

#include "HTTPHandler.hpp"
#include "HTTPReply.hpp"
#include "HTTPRequest.hpp"
#include "InvalidHTTPVersionException.hpp"
#include "Stock.hpp"
#include "Configuration.hpp"
#include "LoginManager.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPReplyHandler : public HTTPHandler
		{
		private:
			ClientRequestType m_requestType;
			std::shared_ptr<AxxonsoftInternProject::Client::LoginManager> m_loginManager;

		private:
			void downloadGettedFile();
			void verifyVersion() override;
			void handleBadRequest();
			void handleNotFound();
			void handleOk();
			void handleStatus();
			void showFolderContent();
			void handleUnauthorized();
			void handleAuthHeader(const HTTPHeader& header);

		public:
			HTTPReplyHandler(
				std::shared_ptr<HTTPReply> handledDocument, 
				ClientRequestType requestType,
				std::shared_ptr<AxxonsoftInternProject::Client::LoginManager> loginManager
			);

			HTTPReplyHandler();
			~HTTPReplyHandler();

			void Handle() override;
		};
	}
}