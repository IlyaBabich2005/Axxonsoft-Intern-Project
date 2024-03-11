#pragma once

#include <memory>

#include "HTTPDocument.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPHandler
		{
		protected:
			std::shared_ptr<HTTPDocument> handledDocument;

		protected: 
			virtual void verifyVersion() = 0;

		public: 
			HTTPHandler(std::shared_ptr<HTTPDocument> handledDocument);

			virtual void Handle() = 0;
		};
	}
}