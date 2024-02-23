#pragma once

#include <memory>

#include "HTTPRequest.hpp"
#include "HTTPHandler.hpp"
#include "HTTPReply.hpp"
#include "InvalidHTTPVersionException.hpp"

using std::shared_ptr,
	  AxxonsoftInternProject::http::exceptions::InvalidHTTPVersionException;

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPRequestHandler : HTTPHandler
		{
		private: 
			void VerifyVersion() override;

		public:
			HTTPRequestHandler(shared_ptr<HTTPDocument> handledDocument);
			virtual ~HTTPRequestHandler();

			void Handle() override;

			//void VerifyURL();
		};
	}
}