#include "HTTPHandler.hpp"

namespace AxxonsoftInternProject
{
	http::HTTPHandler::HTTPHandler(HTTPDocument* document) : 
		document{ document }
	{
	}

	http::HTTPHandler::~HTTPHandler()
	{
	}

	void http::HTTPHandler::VerifyVersion()
	{
		try
		{
			std::stod(this->document->version.substr(5));

			if (this->document->version.substr(0, 5) != "HTTP/")
			{
				throw new InvalidHTTPVersionException{};
			}
		}
		catch (...)
		{
			//some reaction for invalid HTTP
		}
	}
}
