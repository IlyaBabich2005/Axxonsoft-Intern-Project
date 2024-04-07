#pragma once

#include <memory>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

#include <boost/exception/exception.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string/replace.hpp>

#include "HTTPRequest.hpp"
#include "HTTPHandler.hpp"
#include "HTTPReply.hpp"
#include "InvalidHTTPVersionException.hpp"
#include "URIDecoder.hpp"
#include "Configuration.hpp"
#include "DigestManager.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPRequestHandler : public HTTPHandler
		{
		private: 
			std::shared_ptr<HTTPReply> m_outputDocument;
			URIDecoder m_decoder;
			Target m_URITarget;
			std::shared_ptr<AxxonsoftInternProject::SERVER::DigestManager> m_digestManager;
			std::string m_sessionID;
			bool m_isUserLoggedIn;

		private: 
			void verifyVersion() override;
			void handleMethod();
			void handleHeaders();
			void setHeaders();
			std::string getFilePathOnServer(nlohmann::json inputFileInfo);
			std::vector<std::byte> readFileInBinates(std::string pathToFile);
			void putDirectoryContentToReplyBody();
			void putFileToReplyBody(std::ifstream &sendedFile);
			void deleteFile();
			void createDirectories(std::string finalPath);
			void handlePOSTMethod();
			void handleDELETEMethod();
			void handleGetFileMethod();
			void handleGETContentMethod();
			void handleGETMethod();
			void setWWWAuthHeader();
			std::string handleAuthHeaderFields(const std::vector<HTTPHeaderValueClassField>& fields);
			void handleAuthHeader(const HTTPHeader& header);
			void handleCookieHeader(const HTTPHeader& header);
			
		public:
			HTTPRequestHandler(
				std::shared_ptr<HTTPRequest> handledDocument, 
				std::shared_ptr<HTTPReply> outputDocument,
				std::shared_ptr<AxxonsoftInternProject::SERVER::DigestManager> sessionManager);

			void Handle() override;
		};
	}
}