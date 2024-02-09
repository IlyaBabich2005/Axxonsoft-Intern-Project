#pragma once

#include <memory>

#include "HTTPDocument.hpp"

using std::shared_ptr;

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPHandler
		{
		public:
			shared_ptr<HTTPDocument> document;

			HTTPHandler(HTTPDocument* document);
			virtual ~HTTPHandler();

			virtual void Handle();

			void VerifyVersion();
			void VerifyURL();
		};
	}
}