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
			HTTPReplyHandler();
			~HTTPReplyHandler();

			void Handle() override;
		};
	}
}