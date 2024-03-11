#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

#include <boost/exception/exception.hpp>
#include <boost/exception/diagnostic_information.hpp>

#include "HTTPHandler.hpp"
#include "HTTPReply.hpp"
#include "HTTPRequest.hpp"
#include "InvalidHTTPVersionException.hpp"
#include "Stock.hpp"
#include "Configuration.hpp"

namespace exceptions = AxxonsoftInternProject::http::exceptions;
namespace stock = AxxonsoftInternProject::http::stock;
namespace serverConfiguration = AxxonsoftInternProject::SERVER::Configuration;

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPReplyHandler : public HTTPHandler
		{
		private:
			ClientRequestType m_requestType;

		private:
			void downloadGettedFile();
			void verifyVersion() override;
			void handleBadRequest();
			void handleNotFound();
			void handleOk();
			void handleStatus();

		public:
			HTTPReplyHandler(std::shared_ptr<HTTPReply> handledDocument, ClientRequestType requestType);
			~HTTPReplyHandler();

			void Handle() override;
		};
	}
}