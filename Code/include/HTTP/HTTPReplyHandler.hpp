#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

#include "HTTPHandler.hpp"
#include "HTTPReply.hpp"
#include "HTTPRequest.hpp"
#include "InvalidHTTPVersionException.hpp"
#include "Stock.hpp"

namespace exceptions = AxxonsoftInternProject::http::exceptions;
namespace stock = AxxonsoftInternProject::http::stock;

using std::shared_ptr,
	  std::dynamic_pointer_cast,
	  exceptions::InvalidHTTPVersionException;

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPReplyHandler : public HTTPHandler
		{
		private:
			ClientRequestType requestType;

		private:
			void DownloadGettedFile();
			void VerifyVersion() override;
			void HandleBadRequest();
			void HandleNotFound();
			void HandleOk();
			void HandleStatus();

		public:
			HTTPReplyHandler(shared_ptr<HTTPReply> handledDocument, ClientRequestType requestType);
			~HTTPReplyHandler();

			void Handle() override;
		};
	}
}