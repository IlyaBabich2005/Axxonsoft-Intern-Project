#pragma once

#include <memory>

#include "HTTPDocument.hpp"

using std::shared_ptr;

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPDocumentBuilder
		{
		private:
			shared_ptr<HTTPDocument> document;

			HTTPDocumentBuilder(HTTPDocument* document);

			void Reset();

			void SetVersion();
			void SetHeaders();
			void SetBody();
		};
	}
}