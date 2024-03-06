#include "HTTPHandler.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		HTTPHandler::HTTPHandler(shared_ptr<HTTPDocument> handledDocument) :
			handledDocument{ handledDocument }
		{
		}
	}
}