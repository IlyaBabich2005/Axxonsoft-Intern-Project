#pragma once

#include <memory>

#include "HTTPDocument.hpp"
#include "InvalidHTTPVersionException.hpp"

using std::shared_ptr,
	  AxxonsoftInternProject::http::exceptions::InvalidHTTPVersionException;

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPHandler
		{
		protected: 
			shared_ptr<HTTPDocument> document;

		public:
			HTTPHandler(HTTPDocument* document);
			virtual ~HTTPHandler();

			virtual void Handle();

			void VerifyVersion();
			void VerifyURL();
		};
	}
}