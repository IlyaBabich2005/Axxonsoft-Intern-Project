#include "HTTPHandler.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		HTTPHandler::HTTPHandler(std::shared_ptr<HTTPDocument> handledDocument) :
			m_handledDocument{ handledDocument }
		{
		}

		HTTPHandler::HTTPHandler()
		{
		}
	}
}