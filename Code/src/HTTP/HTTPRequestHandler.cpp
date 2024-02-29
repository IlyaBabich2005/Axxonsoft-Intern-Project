#include "HTTPRequestHandler.hpp"

namespace AxxonsoftInternProject
{
	http::HTTPRequestHandler::HTTPRequestHandler(shared_ptr<HTTPRequest> handledDocument, shared_ptr<HTTPReply> outputDocument) :
		HTTPHandler{std::dynamic_pointer_cast<HTTPDocument>(handledDocument), std::dynamic_pointer_cast<HTTPDocument>(outputDocument) }
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

			this->outputDocument->version = this->handledDocument->version;
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

	void http::HTTPRequestHandler::HandleHeaders()
	{
		for (auto header : this->handledDocument->headers)
		{
			if (header.name == "Connection" && header.value == "keep-alive")
			{
				this->outputDocument->headers.push_back(header);
			}
		}
	}

	void http::HTTPRequestHandler::Handle()
	{
		VerifyMethod();
		VerifyVersion();
		HandleHeaders();
	}
}