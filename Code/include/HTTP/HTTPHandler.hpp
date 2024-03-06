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
		protected:
			shared_ptr<HTTPDocument> handledDocument;

		protected: 
			virtual void VerifyVersion() = 0;

		public: 
			HTTPHandler(shared_ptr<HTTPDocument> handledDocument);

			virtual void Handle() = 0;
		};
	}
}