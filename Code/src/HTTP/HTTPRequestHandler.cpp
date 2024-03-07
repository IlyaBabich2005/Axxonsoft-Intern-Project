#include "HTTPRequestHandler.hpp"

namespace AxxonsoftInternProject
{
	http::HTTPRequestHandler::HTTPRequestHandler(shared_ptr<HTTPRequest> handledDocument, shared_ptr<HTTPReply> outputDocument) :
		HTTPHandler{ std::dynamic_pointer_cast<HTTPDocument>(handledDocument) },
		m_outputDocument{ outputDocument }
	{
	}

	void http::HTTPRequestHandler::verifyVersion()
	{
		try
		{
			std::stod(handledDocument->version.substr(5));

			if (handledDocument->version.substr(0, 5) != "HTTP/")
			{
				throw new InvalidHTTPVersionException{};
			}

			m_outputDocument->version = handledDocument->version;
		}
		catch (exception& ex)
		{
			dynamic_pointer_cast<HTTPReply>(m_outputDocument)->status = stock::replyStatuses::g_badRequest;

			handledDocument->version = g_httpVersion;
		}
	}

	void http::HTTPRequestHandler::handleMethod()
	{
		if (m_decoder.Decode(std::dynamic_pointer_cast<HTTPRequest>(handledDocument)->uri, m_URITarget))
		{
			string requestMethod = dynamic_pointer_cast<HTTPRequest>(handledDocument)->method;
			std::cout << "Decoded\n";

			if (requestMethod == g_GET)
				handleGETMethod();
			else if (requestMethod == g_DELETE)
				handleDELETEMethod();
			else if (requestMethod == g_POST)
				handlePOSTMethod();
			else
				dynamic_pointer_cast<HTTPReply>(m_outputDocument)->status = stock::replyStatuses::g_methodNotAllowed;
		}
		else
		{
			std::dynamic_pointer_cast<HTTPReply>(m_outputDocument)->status = stock::replyStatuses::g_notFound;
		}
	}

	void http::HTTPRequestHandler::handleHeaders()
	{
		for (auto header : handledDocument->headers)
		{
			if (header.name == g_connection&& header.value == g_keepAlive)
			{
				m_outputDocument->headers.push_back(header);
			}
		}

		if (m_outputDocument->body.size() != 0)
		{
			m_outputDocument->headers.push_back(HTTPHeader{ g_contentLength, std::to_string(m_outputDocument->body.size()) });
		}
	}

	void http::HTTPRequestHandler::createDirectories(string finalPath)
	{
		string currentPath = g_serverRootDirectory;
		string endPath = finalPath;

		while (!exists(g_serverRootDirectory + finalPath))
		{
			if (!exists(currentPath))
			{
				create_directory(currentPath);
			}
			else
			{
				if (endPath.find('/') == string::npos)
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

	void http::HTTPRequestHandler::handlePOSTMethod()
	{
		if (m_URITarget.components.size() != 0)
		{
			m_outputDocument->status = stock::replyStatuses::g_notFound;
			return;
		}
		else
		{
			try
			{
				json inputFileInfo = json::parse(handledDocument->body);
				vector<byte> bytes = inputFileInfo["data"];

				createDirectories(string{ inputFileInfo["path"] });

				string pathToFile = g_serverRootDirectory + string{inputFileInfo["path"]} + "/" + string{inputFileInfo["filename"]};

				ofstream file{ pathToFile, ios::binary | ios::trunc};

				if (file.is_open())
				{
					file.write((char*)bytes.data(), bytes.size());
				}

				file.close();
			}
			catch (exception& ex)
			{
				m_outputDocument->status = stock::replyStatuses::g_notFound;
			}
		}
	}

	vector<byte> http::HTTPRequestHandler::readFileInBinates(string pathToFile)
	{
		ifstream file(pathToFile, ios::binary | ios::ate);

		auto end = file.tellg();
		file.seekg(0, ios::beg);

		auto size = size_t(end - file.tellg());
		vector<byte> buffer(size);

		file.read((char*)buffer.data(), buffer.size());

		return buffer;
	}

	void http::HTTPRequestHandler::putFileToReplyBody(ifstream &sendedFile)
	{
		json sendedInfo;
		json gettedFileInfo = json::parse(handledDocument->body);

		std::cout << "Readed\n";

		sendedInfo["data"] = readFileInBinates(g_serverRootDirectory + string{gettedFileInfo["path"]} + "/" + string{ gettedFileInfo["filename"] });
		sendedInfo["filename"] = string{ gettedFileInfo["filename"] };

		m_outputDocument->body = sendedInfo.dump(4);

		std::cout << "Writed in file\n";
	}

	void http::HTTPRequestHandler::handleGetFileMethod()
	{
		json fileInfo = json::parse(handledDocument->body);

		ifstream sendedFile{ g_serverRootDirectory + string{fileInfo["path"]} + "/" + string{fileInfo["filename"]}};

		if (sendedFile.is_open())
		{
			std::cout << "Openning file\n";

			putFileToReplyBody(sendedFile);
			m_outputDocument->status = stock::replyStatuses::g_ok;
		}
		else
		{
			m_outputDocument->status = stock::replyStatuses::g_notFound;
		}
		
		sendedFile.close();
	}

	void http::HTTPRequestHandler::putDirectoryContentToReplyBody()
	{
		json directoryInfo = json::parse(handledDocument->body);
		json directoryContent;

		string path = directoryInfo["path"];

		for (const auto& file : directory_iterator(g_serverRootDirectory + path))
		{
			std::cout << file << "\n";
			directoryContent["content"].push_back(file.path());
		}

		std::cout << "Serializing body\n";

		m_outputDocument->body = directoryContent.dump(4);
	}

	void http::HTTPRequestHandler::deleteFile()
	{
		json deletedFileInfo = json::parse(handledDocument->body);

		if (exists(g_serverRootDirectory + string{ deletedFileInfo["path"] } + "/" + string{ deletedFileInfo["filename"] }))
		{
			remove_all(g_serverRootDirectory + string{ deletedFileInfo["path"] } + "/" + string{ deletedFileInfo["filename"] });
			m_outputDocument->status = stock::replyStatuses::g_ok;
		}
		else
		{
			m_outputDocument->status = stock::replyStatuses::g_notFound;
		}
	}

	void http::HTTPRequestHandler::handleDELETEMethod()
	{
		if (m_URITarget.components.size() != 0)
		{
			m_outputDocument->status = stock::replyStatuses::g_notFound;
			return;
		}

		try
		{
			deleteFile();
		}
		catch(exception& ex)
		{
			m_outputDocument->status = stock::replyStatuses::g_notFound;
		}
	}

	void http::HTTPRequestHandler::handleGETContentMethod()
	{
			try
			{
				putDirectoryContentToReplyBody();

				m_outputDocument->status = stock::replyStatuses::g_ok;
				cout << "Sucksessfully checked\n";
			}
			catch (exception& ex)
			{
				m_outputDocument->status = stock::replyStatuses::g_notFound;
			}
	}

	void http::HTTPRequestHandler::handleGETMethod()
	{
		try
		{
			if (m_URITarget.components.size() == 1 && m_URITarget.components[0] == g_content)
			{
				std::cout << "Scan directory\n";

				handleGETContentMethod();
			}
			else if (m_URITarget.components.size() == 0)
			{
				std::cout << "Search file\n";

				handleGetFileMethod();
			}
			else
			{
				m_outputDocument->status = stock::replyStatuses::g_notFound;
			}
		}
		catch (exception& ex)
		{
			m_outputDocument->status = stock::replyStatuses::g_notFound;
		}
	}

	void http::HTTPRequestHandler::Handle()
	{
		verifyVersion();
		handleMethod();
		handleHeaders();
	}
}