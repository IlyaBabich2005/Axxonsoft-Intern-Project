#include "HTTPRequestHandler.hpp"

namespace AxxonsoftInternProject
{
	http::HTTPRequestHandler::HTTPRequestHandler(std::shared_ptr<HTTPRequest> handledDocument, std::shared_ptr<HTTPReply> outputDocument) :
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
				throw new exceptions::InvalidHTTPVersionException{};
			}

			m_outputDocument->version = handledDocument->version;
		}
		catch (std::exception& ex)
		{
			std::dynamic_pointer_cast<HTTPReply>(m_outputDocument)->status = stock::replyStatuses::g_badRequest;

			handledDocument->version = serverConfiguration::g_httpVersion;
		}
	}

	void http::HTTPRequestHandler::handleMethod()
	{
		if (m_decoder.Decode(std::dynamic_pointer_cast<HTTPRequest>(handledDocument)->uri, m_URITarget))
		{
			string requestMethod = std::dynamic_pointer_cast<HTTPRequest>(handledDocument)->method;
			std::cout << "Decoded\n";

			if (requestMethod == requestMethods::g_GET)
				handleGETMethod();
			else if (requestMethod == requestMethods::g_DELETE)
				handleDELETEMethod();
			else if (requestMethod == requestMethods::g_POST)
				handlePOSTMethod();
			else
				std::dynamic_pointer_cast<HTTPReply>(m_outputDocument)->status = stock::replyStatuses::g_methodNotAllowed;
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
			if (header.name == headers::names::g_connection&& header.value == headers::values::g_keepAlive)
			{
				m_outputDocument->headers.push_back(header);
			}
		}

		if (m_outputDocument->body.size() != 0)
		{
			m_outputDocument->headers.push_back(HTTPHeader{ headers::names::g_contentLength, std::to_string(m_outputDocument->body.size()) });
		}
	}

	void http::HTTPRequestHandler::createDirectories(string finalPath)
	{
		string currentPath = serverConfiguration::g_serverRootDirectory;
		string endPath = finalPath;

		while (filesystem::exists(serverConfiguration::g_serverRootDirectory + finalPath))
		{
			if (!filesystem::exists(currentPath))
			{
				filesystem::create_directory(currentPath);
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
				nlohmann::json inputFileInfo = nlohmann::json::parse(handledDocument->body);
				std::vector<std::byte> bytes = inputFileInfo["data"];

				createDirectories(string{ inputFileInfo["path"] });

				string pathToFile = serverConfiguration::g_serverRootDirectory + string{inputFileInfo["path"]} + "/" + string{inputFileInfo["filename"]};

				std::ofstream file{ pathToFile, std::ios::binary | std::ios::trunc};

				if (file.is_open())
				{
					file.write((char*)bytes.data(), bytes.size());
				}

				file.close();
			}
			catch (std::exception& ex)
			{
				m_outputDocument->status = stock::replyStatuses::g_notFound;
			}
		}
	}

	std::vector<std::byte> http::HTTPRequestHandler::readFileInBinates(string pathToFile)
	{
		std::ifstream file(pathToFile, std::ios::binary | std::ios::ate);

		auto end = file.tellg();
		file.seekg(0, std::ios::beg);

		auto size = size_t(end - file.tellg());
		std::vector<std::byte> buffer(size);

		file.read((char*)buffer.data(), buffer.size());

		return buffer;
	}

	void http::HTTPRequestHandler::putFileToReplyBody(std::ifstream &sendedFile)
	{
		nlohmann::json sendedInfo;
		nlohmann::json gettedFileInfo = nlohmann::json::parse(handledDocument->body);

		std::cout << "Readed\n";

		sendedInfo["data"] = readFileInBinates(serverConfiguration::g_serverRootDirectory + string{gettedFileInfo["path"]} + "/" + string{ gettedFileInfo["filename"] });
		sendedInfo["filename"] = string{ gettedFileInfo["filename"] };

		m_outputDocument->body = sendedInfo.dump(4);

		std::cout << "Writed in file\n";
	}

	void http::HTTPRequestHandler::handleGetFileMethod()
	{
		nlohmann::json fileInfo = nlohmann::json::parse(handledDocument->body);

		std::ifstream sendedFile{ serverConfiguration::g_serverRootDirectory + string{fileInfo["path"]} + "/" + string{fileInfo["filename"]}};

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
		nlohmann::json directoryInfo = nlohmann::json::parse(handledDocument->body);
		nlohmann::json directoryContent;

		string path = directoryInfo["path"];

		for (const auto& file : filesystem::directory_iterator(serverConfiguration::g_serverRootDirectory + path))
		{
			std::cout << file << "\n";
			directoryContent["content"].push_back(file.path());
		}

		std::cout << "Serializing body\n";

		m_outputDocument->body = directoryContent.dump(4);
	}

	void http::HTTPRequestHandler::deleteFile()
	{
		nlohmann::json deletedFileInfo = nlohmann::json::parse(handledDocument->body);

		if (filesystem::exists(serverConfiguration::g_serverRootDirectory + string{ deletedFileInfo["path"] } + "/" + string{ deletedFileInfo["filename"] }))
		{
			filesystem::remove_all(serverConfiguration::g_serverRootDirectory + string{ deletedFileInfo["path"] } + "/" + string{ deletedFileInfo["filename"] });
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
		catch(std::exception& ex)
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
				std::cout << "Sucksessfully checked\n";
			}
			catch (std::exception& ex)
			{
				m_outputDocument->status = stock::replyStatuses::g_notFound;
			}
	}

	void http::HTTPRequestHandler::handleGETMethod()
	{
		try
		{
			if (m_URITarget.components.size() == 1 && m_URITarget.components[0] == uri::components::g_content)
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
		catch (std::exception& ex)
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