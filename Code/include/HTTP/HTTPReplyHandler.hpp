#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

#include "HTTPHandler.hpp"
#include "HTTPReply.hpp"
#include "HTTPRequest.hpp"
#include "InvalidHTTPVersionException.hpp"
#include "Stock.hpp"
#include "Configuration.hpp"

namespace exceptions = AxxonsoftInternProject::http::exceptions;
namespace stock = AxxonsoftInternProject::http::stock;

using std::shared_ptr,
	  std::stod,
	  std::cout,
	  std::ofstream, 
	  std::ios,
	  std::byte,
	  std::dynamic_pointer_cast,
	  AxxonsoftInternProject::SERVER::Configuration::g_httpVersion,
	  AxxonsoftInternProject::SERVER::Configuration::g_serverRootDirectory,
	  exceptions::InvalidHTTPVersionException;

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
			HTTPReplyHandler(shared_ptr<HTTPReply> handledDocument, ClientRequestType requestType);
			~HTTPReplyHandler();

			void Handle() override;
		};
	}
}