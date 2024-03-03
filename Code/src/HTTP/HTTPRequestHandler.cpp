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

	void http::HTTPRequestHandler::HandleMethod()
	{
		if (this->decoder.Decode(std::dynamic_pointer_cast<HTTPRequest>(this->handledDocument)->uri, this->URITarget))
		{
			string requestMethod = dynamic_pointer_cast<HTTPRequest>(this->handledDocument)->method;
			std::cout << "Decoded\n";

			if (requestMethod == "GET")
				this->HandleGETMethod();
			else if (requestMethod == "DELETE")
				this->HandleDELETEMethod();
			else if (requestMethod == "POST")
				this->HandlePOSTMethod();
			else
				dynamic_pointer_cast<HTTPReply>(this->outputDocument)->status = stock::replyStatuses::methodNotAllowed;
		}
		else
		{
			std::dynamic_pointer_cast<HTTPReply>(this->outputDocument)->status = stock::replyStatuses::notFound;
		}
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

	void http::HTTPRequestHandler::CreateDirectories(string finalPath)
	{
		string currentPath = "./files/";
		string endPath = finalPath;

		while (!exists("./files/" + finalPath))
		{
			if (!exists(currentPath))
			{
				create_directory(currentPath);
			}
			else
			{
				if (endPath.find('/') == std::string::npos)
				{
					currentPath += endPath;
				}
				else
				{
					currentPath += endPath.substr(0, endPath.find('/')) + "/";
					endPath.erase(0, endPath.find('/') + 1);
				}
			}
		}
	}

	void http::HTTPRequestHandler::HandlePOSTMethod()
	{
		if (this->URITarget.components.size() != 0)
		{
			std::dynamic_pointer_cast<HTTPReply>(this->outputDocument)->status = stock::replyStatuses::notFound;
			return;
		}
		else
		{
			try
			{
				json inputFileInfo = json::parse(this->handledDocument->body);
				vector<unsigned char> bytes = inputFileInfo["data"];

				this->CreateDirectories(string{ inputFileInfo["path"] });

				string pathToFile = "./files/" + string{inputFileInfo["path"]} + "/" + string{inputFileInfo["filename"]};

				std::ofstream file{ pathToFile, std::ios::binary | std::ios::trunc};

				if (file.is_open())
				{
					std::copy(bytes.begin(), bytes.end(), std::ostreambuf_iterator<char>(file));
				}

				file.close();
			}
			catch (...)
			{
				std::dynamic_pointer_cast<HTTPReply>(this->outputDocument)->status = stock::replyStatuses::notFound;
			}
		}
	}

	void http::HTTPRequestHandler::PutFileToReplyBody(ifstream &sendedFile)
	{
		json sendedInfo;
		json gettedFileInfo = json::parse(this->handledDocument->body);

		std::vector<unsigned char> bytes(std::istreambuf_iterator<char>(sendedFile), {});

		std::cout << "Readed\n";

		sendedInfo["data"] = bytes;
		sendedInfo["filename"] = string{ gettedFileInfo["filename"] };

		this->outputDocument->body = sendedInfo.dump(4);

		std::cout << "Writed in file\n";
	}

	void http::HTTPRequestHandler::HandleGetFileMethod()
	{
		json fileInfo = json::parse(this->handledDocument->body);

		ifstream sendedFile{ "./files/" + string{fileInfo["path"]} + "/" + string{fileInfo["filename"]}};

		if (sendedFile.is_open())
		{
			std::cout << "Openning file\n";

			this->PutFileToReplyBody(sendedFile);
			dynamic_pointer_cast<HTTPReply>(this->outputDocument)->status = stock::replyStatuses::ok;
		}
		else
		{
			dynamic_pointer_cast<HTTPReply>(this->outputDocument)->status = stock::replyStatuses::notFound;
		}
		
		sendedFile.close();
	}

	void http::HTTPRequestHandler::PutDirectoryContentToReplyBody()
	{
		json directoryInfo = json::parse(this->handledDocument->body);
		json directoryContent;

		string path = directoryInfo["path"];

		for (const auto& file : directory_iterator("./files" + path))
		{
			std::cout << file << "\n";
			directoryContent["content"].push_back(file.path());
		}

		std::cout << "Serializing body\n";

		this->outputDocument->body = directoryContent.dump(4);
	}

	void http::HTTPRequestHandler::DeleteFile()
	{
		json deletedFileInfo = json::parse(this->handledDocument->body);

		if (exists("./files/" + string{ deletedFileInfo["path"] } + "/" + string{ deletedFileInfo["filename"] }))
		{
			remove_all("./files/" + string{ deletedFileInfo["path"] } + "/" + string{ deletedFileInfo["filename"] });
			dynamic_pointer_cast<HTTPReply>(this->outputDocument)->status = stock::replyStatuses::ok;
		}
		else
		{
			dynamic_pointer_cast<HTTPReply>(this->outputDocument)->status = stock::replyStatuses::notFound;
		}
	}

	void http::HTTPRequestHandler::HandleDELETEMethod()
	{
		if (this->URITarget.components.size() != 0)
		{
			dynamic_pointer_cast<HTTPReply>(this->outputDocument)->status = stock::replyStatuses::notFound;
			return;
		}

		try
		{
			this->DeleteFile();
		}
		catch(...)
		{
			dynamic_pointer_cast<HTTPReply>(this->outputDocument)->status = stock::replyStatuses::notFound;
		}
	}

	void http::HTTPRequestHandler::HandleGETContentMethod()
	{
			try
			{
				this->PutDirectoryContentToReplyBody();

				dynamic_pointer_cast<HTTPReply>(this->outputDocument)->status = stock::replyStatuses::ok;
				std::cout << "Sucksessfully checked\n";
			}
			catch (...)
			{
				dynamic_pointer_cast<HTTPReply>(this->outputDocument)->status = stock::replyStatuses::notFound;
			}
	}

	void http::HTTPRequestHandler::HandleGETMethod()
	{
		try
		{
			if (this->URITarget.components.size() == 1 && this->URITarget.components[1] == "content")
			{
				std::cout << "Scan directory\n";

				this->HandleGETContentMethod();
			}
			else if (this->URITarget.components.size() == 0)
			{
				std::cout << "Search file\n";

				this->HandleGetFileMethod();
			}
			else
			{
				dynamic_pointer_cast<HTTPReply>(this->outputDocument)->status = stock::replyStatuses::notFound;
			}
		}
		catch (...)
		{
			dynamic_pointer_cast<HTTPReply>(this->outputDocument)->status = stock::replyStatuses::notFound;
		}
	}

	void http::HTTPRequestHandler::Handle()
	{
		VerifyVersion();
		HandleMethod();
		HandleHeaders();
	}
}