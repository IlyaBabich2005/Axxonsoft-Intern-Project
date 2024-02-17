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
		if (this->document->version.substr(0, 5) == "HTTP/")
		{
			try
			{
				std::stod(this->document->version.substr(5));
			}
			catch (...)
			{
				
			}
		}
		else
		{
			//some reaction for invalid HTTP
		}
	}


}
