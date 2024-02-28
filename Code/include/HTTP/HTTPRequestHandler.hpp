#pragma once

#include <memory>

#include "HTTPRequest.hpp"
#include "HTTPHandler.hpp"
#include "HTTPReply.hpp"
#include "InvalidHTTPVersionException.hpp"
#include "Stock.hpp"

namespace exceptions = AxxonsoftInternProject::http::exceptions;
namespace stock = AxxonsoftInternProject::http::stock;

using std::shared_ptr,
	  std::dynamic_pointer_cast,
	  stock::replyStatuses::badRequest,
	  stock::replyStatuses::ok,
	  exceptions::InvalidHTTPVersionException;

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPRequestHandler : public HTTPHandler
		{
		private: 
			void VerifyVersion() override;
			void VerifyMethod();

		public:
			HTTPRequestHandler(shared_ptr<HTTPRequest> handledDocument);

			void Handle() override;

			//void VerifyURL();
		};
	}
}