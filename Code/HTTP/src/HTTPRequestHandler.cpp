#include "HTTPRequestHandler.hpp"

namespace AxxonsoftInternProject
{
	http::HTTPRequestHandler::HTTPRequestHandler(shared_ptr<HTTPDocument> handledDocument) : 
		HTTPHandler{handledDocument, std::make_shared<HTTPDocument>(new HTTPReply)}
	{

	}

	http::HTTPRequestHandler::~HTTPRequestHandler()
	{
	}

	void http::HTTPRequestHandler::VerifyVersion()
	{
		try
		{
			std::stod(this->handledDocument->version.substr(5));

			if (this->handledDocument->version.substr(0, 5) != "HTTP/")
			{
				throw new InvalidHTTPVersionException{};
			}
			else
			{

			}
		}
		catch (...)
		{
			//some reaction for invalid HTTP
		}
	}
}