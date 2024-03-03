#include "HTTPHandler.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		HTTPHandler::HTTPHandler(shared_ptr<HTTPDocument> handledDocument, shared_ptr<HTTPDocument> outputDocument) :
			handledDocument{ handledDocument },
			outputDocument{ outputDocument }
		{
		}
	}
}