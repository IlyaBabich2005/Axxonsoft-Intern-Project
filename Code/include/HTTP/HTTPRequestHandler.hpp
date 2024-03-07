#pragma once

#include <memory>
#include <iostream>
#include <fstream>

#include "HTTPRequest.hpp"
#include "HTTPHandler.hpp"
#include "HTTPReply.hpp"
#include "InvalidHTTPVersionException.hpp"
#include "URIDecoder.hpp"
#include "Configuration.hpp"

namespace exceptions = AxxonsoftInternProject::http::exceptions;
namespace stock = AxxonsoftInternProject::http::stock;

using std::shared_ptr,
	  std::dynamic_pointer_cast,
	  std::filesystem::directory_iterator,
	  std::filesystem::remove_all,
	  std::filesystem::exists,
	  std::filesystem::create_directory,
	  std::byte,
	  std::ifstream,
	  std::ofstream,
	  std::stod,
	  std::cout,
	  std::ios,
	  AxxonsoftInternProject::SERVER::Configuration::g_httpVersion,
	  AxxonsoftInternProject::SERVER::Configuration::g_serverRootDirectory,
	  AxxonsoftInternProject::http::URIDecoder,
	  AxxonsoftInternProject::http::DecoderStatus,
	  stock::requestMethods::g_GET,
	  stock::requestMethods::g_POST,
	  stock::requestMethods::g_DELETE,
	  stock::headers::names::g_connection,
	  stock::headers::names::g_contentLength,
	  stock::headers::values::g_keepAlive,
	  stock::uri::components::g_content,
	  exceptions::InvalidHTTPVersionException;

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPRequestHandler : public HTTPHandler
		{
		private: 
			shared_ptr<HTTPReply> m_outputDocument;
			URIDecoder m_decoder;
			Target m_URITarget;

		private: 
			void verifyVersion() override;
			void handleMethod();
			void handleHeaders();
			vector<std::byte> readFileInBinates(string pathToFile);
			void putDirectoryContentToReplyBody();
			void putFileToReplyBody(ifstream &sendedFile);
			void deleteFile();
			void createDirectories(string finalPath);
			void handlePOSTMethod();
			void handleDELETEMethod();
			void handleGetFileMethod();
			void handleGETContentMethod();
			void handleGETMethod();
			
		public:
			HTTPRequestHandler(shared_ptr<HTTPRequest> handledDocument, shared_ptr<HTTPReply> outputDocument);

			void Handle() override;
		};
	}
}