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
			std::stod(m_handledDocument->m_version.substr(5));

			if (m_handledDocument->m_version.substr(0, 5) != "HTTP/")
			{
				throw new exceptions::InvalidHTTPVersionException{};
			}

			m_outputDocument->m_version = m_handledDocument->m_version;
		}
		catch (std::exception& ex)
		{
			std::dynamic_pointer_cast<HTTPReply>(m_outputDocument)->m_status = stock::replyStatuses::g_badRequest;
			std::cout << ex.what() << "\n";
			m_handledDocument->m_version = AxxonsoftInternProject::SERVER::Configuration::g_httpVersion;
		}
		catch (boost::exception& ex)
		{
			std::dynamic_pointer_cast<HTTPReply>(m_outputDocument)->m_status = stock::replyStatuses::g_badRequest;
			std::cout << boost::diagnostic_information(ex) << '\n';
			m_handledDocument->m_version = AxxonsoftInternProject::SERVER::Configuration::g_httpVersion;
		}
	}

	void http::HTTPRequestHandler::handleMethod()
	{
		if (m_decoder.Decode(std::dynamic_pointer_cast<HTTPRequest>(m_handledDocument)->m_uri, m_URITarget))
		{
			std::string requestMethod = std::dynamic_pointer_cast<HTTPRequest>(m_handledDocument)->m_method;
			std::cout << "Decoded\n";

			if (requestMethod == stock::requestMethods::g_GET)
				handleGETMethod();
			else if (requestMethod == stock::requestMethods::g_DELETE)
				handleDELETEMethod();
			else if (requestMethod == stock::requestMethods::g_POST)
				handlePOSTMethod();
			else
				std::dynamic_pointer_cast<HTTPReply>(m_outputDocument)->m_status = stock::replyStatuses::g_methodNotAllowed;
		}
		else
		{
			std::dynamic_pointer_cast<HTTPReply>(m_outputDocument)->m_status = stock::replyStatuses::g_notFound;
		}
	}

	void http::HTTPRequestHandler::handleHeaders()
	{
		for (auto header : m_handledDocument->m_headers)
		{
			if (header.m_name == stock::headers::names::g_connection && header.m_value == stock::headers::values::g_keepAlive)
			{
				m_outputDocument->m_headers.push_back(header);
			}
		}

		if (m_outputDocument->m_body.size() != 0)
		{
			m_outputDocument->m_headers.push_back(HTTPHeader{ stock::headers::names::g_contentLength, std::to_string(m_outputDocument->m_body.size()) });
		}
	}

	void http::HTTPRequestHandler::createDirectories(std::string finalPath)
	{
		std::string currentPath = AxxonsoftInternProject::SERVER::Configuration::g_serverRootDirectory;
		std::string endPath = finalPath;

		while (std::filesystem::exists(AxxonsoftInternProject::SERVER::Configuration::g_serverRootDirectory + finalPath))
		{
			if (!std::filesystem::exists(currentPath))
			{
				std::filesystem::create_directory(currentPath);
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

	void http::HTTPRequestHandler::handlePOSTMethod()
	{
		if (m_URITarget.components.size() != 0)
		{
			m_outputDocument->m_status = stock::replyStatuses::g_notFound;
			return;
		}
		else
		{
			try
			{
				nlohmann::json inputFileInfo = nlohmann::json::parse(m_handledDocument->m_body);
				std::vector<std::byte> bytes = inputFileInfo["data"];

				createDirectories(std::string{ inputFileInfo["path"] });

				std::string pathToFile = AxxonsoftInternProject::SERVER::Configuration::g_serverRootDirectory + 
					std::string{inputFileInfo["path"]} + "/" + std::string{inputFileInfo["filename"]};

				std::ofstream file{ pathToFile, std::ios::binary | std::ios::trunc};

				if (file.is_open())
				{
					file.write((char*)bytes.data(), bytes.size());
				}

				file.close();
			}
			catch (std::exception& ex)
			{
				std::cout << ex.what() << '\n';
				m_outputDocument->m_status = stock::replyStatuses::g_notFound;
			}
			catch (boost::exception& ex)
			{
				std::cout << boost::diagnostic_information(ex) << '\n';
				m_outputDocument->m_status = stock::replyStatuses::g_notFound;
			}
		}
	}

	std::vector<std::byte> http::HTTPRequestHandler::readFileInBinates(std::string pathToFile)
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
		nlohmann::json gettedFileInfo = nlohmann::json::parse(m_handledDocument->m_body);

		std::cout << "Readed\n";

		sendedInfo["data"] = readFileInBinates(AxxonsoftInternProject::SERVER::Configuration::g_serverRootDirectory + 
			std::string{gettedFileInfo["path"]} + "/" + std::string{ gettedFileInfo["filename"] });
		sendedInfo["filename"] = std::string{ gettedFileInfo["filename"] };

		m_outputDocument->m_body = sendedInfo.dump(stock::json::g_dumpSize);

		std::cout << "Writed in file\n";
	}

	void http::HTTPRequestHandler::handleGetFileMethod()
	{
		nlohmann::json fileInfo = nlohmann::json::parse(m_handledDocument->m_body);

		std::ifstream sendedFile{ AxxonsoftInternProject::SERVER::Configuration::g_serverRootDirectory + 
			std::string{fileInfo["path"]} + "/" + std::string{fileInfo["filename"]}};

		if (sendedFile.is_open())
		{
			std::cout << "Openning file\n";

			putFileToReplyBody(sendedFile);
			m_outputDocument->m_status = stock::replyStatuses::g_ok;
		}
		else
		{
			m_outputDocument->m_status = stock::replyStatuses::g_notFound;
		}
		
		sendedFile.close();
	}

	void http::HTTPRequestHandler::putDirectoryContentToReplyBody()
	{
		nlohmann::json directoryInfo = nlohmann::json::parse(m_handledDocument->m_body);
		nlohmann::json directoryContent;

		std::string path = directoryInfo["path"];

		for (const auto& file : std::filesystem::directory_iterator(AxxonsoftInternProject::SERVER::Configuration::g_serverRootDirectory + path))
		{
			std::cout << file << "\n";
			directoryContent["content"].push_back(file.path());
		}

		std::cout << "Serializing body\n";

		m_outputDocument->m_body = directoryContent.dump(stock::json::g_dumpSize);
	}

	void http::HTTPRequestHandler::deleteFile()
	{
		nlohmann::json deletedFileInfo = nlohmann::json::parse(m_handledDocument->m_body);

		if (std::filesystem::exists(AxxonsoftInternProject::SERVER::Configuration::g_serverRootDirectory + 
			std::string{ deletedFileInfo["path"] } + "/" + std::string{ deletedFileInfo["filename"] }))
		{
			std::filesystem::remove_all(AxxonsoftInternProject::SERVER::Configuration::g_serverRootDirectory + 
				std::string{ deletedFileInfo["path"] } + "/" + std::string{ deletedFileInfo["filename"] });
			m_outputDocument->m_status = stock::replyStatuses::g_ok;
		}
		else
		{
			m_outputDocument->m_status = stock::replyStatuses::g_notFound;
		}
	}

	void http::HTTPRequestHandler::handleDELETEMethod()
	{
		if (m_URITarget.components.size() != 0)
		{
			m_outputDocument->m_status = stock::replyStatuses::g_notFound;
			return;
		}

		try
		{
			deleteFile();
		}
		catch(std::exception& ex)
		{
			std::cout << ex.what() << '\n';
			m_outputDocument->m_status = stock::replyStatuses::g_notFound;
		}
		catch (boost::exception& ex)
		{
			std::cout << boost::diagnostic_information(ex) << '\n';
			m_outputDocument->m_status = stock::replyStatuses::g_notFound;
		}
	}

	void http::HTTPRequestHandler::handleGETContentMethod()
	{
			try
			{
				putDirectoryContentToReplyBody();

				m_outputDocument->m_status = stock::replyStatuses::g_ok;
				std::cout << "Sucksessfully checked\n";
			}
			catch (std::exception& ex)
			{
				std::cout << ex.what() << '\n';
				m_outputDocument->m_status = stock::replyStatuses::g_notFound;
			}
			catch (boost::exception& ex)
			{
				std::cout << boost::diagnostic_information(ex) << '\n';
				m_outputDocument->m_status = stock::replyStatuses::g_notFound;
			}
	}

	void http::HTTPRequestHandler::handleGETMethod()
	{
		try
		{
			if (m_URITarget.components.size() == 1 && m_URITarget.components[0] == stock::uri::components::g_content)
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
				m_outputDocument->m_status = stock::replyStatuses::g_notFound;
			}
		}
		catch (std::exception& ex)
		{
			std::cout << ex.what() << "\n";
			m_outputDocument->m_status = stock::replyStatuses::g_notFound;
		}
		catch (boost::exception& ex)
		{
			std::cout << boost::diagnostic_information(ex) << "\n";
			m_outputDocument->m_status = stock::replyStatuses::g_notFound;
		}
	}

	void http::HTTPRequestHandler::Handle()
	{
		verifyVersion();
		handleMethod();
		handleHeaders();
	}
}