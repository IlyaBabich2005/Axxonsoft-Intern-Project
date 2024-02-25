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

			if (this->handledDocument->version.substr(0, 5) == "HTTP/")
			{
				throw new InvalidHTTPVersionException{};
			}

			this->handledDocument->version = this->handledDocument->version;
		}
		catch (...)
		{
			dynamic_pointer_cast<HTTPReply>(this->outputDocument)->status = badRequest;

			this->handledDocument->version = "HTTP/1.0";
		}
	}

	void http::HTTPRequestHandler::VerifyMethod()
	{
		for (auto method : requestMethods)
		{
			if (dynamic_pointer_cast<HTTPRequest>(this->handledDocument)->method == method)
			{
				return;
			}
		}

		dynamic_pointer_cast<HTTPReply>(this->outputDocument)->status = badRequest;
	}

	void http::HTTPRequestHandler::Handle()
	{
		VerifyMethod();
		VerifyVersion();
	}
}