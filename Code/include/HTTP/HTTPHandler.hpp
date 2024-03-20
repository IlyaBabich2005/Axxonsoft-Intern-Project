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
			std::shared_ptr<HTTPDocument> m_handledDocument;

		protected: 
			virtual void verifyVersion() = 0;

		public: 
			HTTPHandler(std::shared_ptr<HTTPDocument> handledDocument);
			HTTPHandler();

			virtual void Handle() = 0;
		};
	}
}