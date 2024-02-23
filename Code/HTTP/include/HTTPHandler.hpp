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
			shared_ptr<HTTPDocument> outputDocument;

		protected: 
			virtual void VerifyVersion() = 0;

		public: 
			HTTPHandler(shared_ptr<HTTPDocument> handledDocument, shared_ptr<HTTPDocument> outputDocument);

			virtual void Handle() = 0;
		};
	}
}