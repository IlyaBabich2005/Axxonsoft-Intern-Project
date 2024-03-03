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
			dynamic_pointer_cast<HTTPReply>(this->outputDocument)->status = stock::replyStatuses::badRequest;

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

		dynamic_pointer_cast<HTTPReply>(this->outputDocument)->status = stock::replyStatuses::methodNotAllowed;
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

		if (this->outputDocument->body.size() != 0)
		{
			this->outputDocument->headers.push_back(HTTPHeader{ "Content-Length", std::to_string(this->outputDocument->body.size()) });
		}
	}

	void http::HTTPRequestHandler::PutFileToReplyBody(ifstream &sendedFile)
	{
		size_t buffer_size{ 1<<20 };
		char* buffer{ new char[buffer_size] };
		json sendedInfo;
		string filename{ this->URITarget.components[this->URITarget.components.size() - 1] };

		while (sendedFile)
		{
			sendedFile.read(buffer, buffer_size);

			size_t count{ static_cast<size_t>(sendedFile.gcount()) };

			if (!count)
			{
				break;
			}
		}

		sendedInfo["file"] = string{ buffer };
		sendedInfo["format"] = filename.substr(filename.find('.'));

		this->outputDocument->body = sendedInfo.dump(4);

		delete[] buffer;
	}

	void http::HTTPRequestHandler::HandleGetFileMethod()
	{
		if (!this->URITarget.isFile)
		{
			ifstream sendedFile{ "./" + std::dynamic_pointer_cast<HTTPRequest>(this->handledDocument)->uri.substr(8)};

			if (sendedFile.is_open())
			{
				this->PutFileToReplyBody(sendedFile);
			}
			else
			{
				dynamic_pointer_cast<HTTPReply>(this->outputDocument)->status = stock::replyStatuses::notFound;
			}
		}
		else
		{
			dynamic_pointer_cast<HTTPReply>(this->outputDocument)->status = stock::replyStatuses::notFound;
		}
	}

	void http::HTTPRequestHandler::PutDirectoryContentToReplyBody()
	{
		json directoryContent;

		for (const auto& file : directory_iterator("./" + std::dynamic_pointer_cast<HTTPRequest>(this->handledDocument)->uri.substr(8)))
		{
			std::cout << file << "\n";
			directoryContent["content"].push_back(file.path());
		}

		std::cout << "Serializing body\n";

		this->outputDocument->body = directoryContent.dump(4);
	}

	void http::HTTPRequestHandler::HandleGETContentMethod()
	{
			std::cout << "Content detected\n";

			if (this->URITarget.isFile)
			{
				dynamic_pointer_cast<HTTPReply>(this->outputDocument)->status = stock::replyStatuses::notFound;
			}
			else
			{
				std::cout << "Checking directory\n";

				try
				{
					this->PutDirectoryContentToReplyBody();

					std::cout << "Sucksessfully checked\n";
				}
				catch (...)
				{
					dynamic_pointer_cast<HTTPReply>(this->outputDocument)->status = stock::replyStatuses::notFound;
				}
			}
	}

	void http::HTTPRequestHandler::HandleGETMethod()
	{
		if (this->decoder.Decode(std::dynamic_pointer_cast<HTTPRequest>(this->handledDocument)->uri, this->URITarget))
		{
			std::cout << "Decoded\n";

			if (this->URITarget.components.size() > 1 && this->URITarget.components[1] == "content")
			{
				this->HandleGETContentMethod();
			}
			else if (this->URITarget.isFile)
			{
				this->HandleGetFileMethod();
			}
		}
		else
		{
			std::dynamic_pointer_cast<HTTPReply>(this->outputDocument)->status = stock::replyStatuses::notFound;
		}
	}

	void http::HTTPRequestHandler::Handle()
	{
		VerifyMethod();
		VerifyVersion();
		HandleGETMethod();
		HandleHeaders();
	}
}