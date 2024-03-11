#include "HTTPHandler.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		HTTPHandler::HTTPHandler(std::shared_ptr<HTTPDocument> handledDocument) :
			handledDocument{ handledDocument }
		{
		}
	}
}