#pragma once

#include <memory>
#include <iostream>
#include <fstream>

#include "HTTPRequest.hpp"
#include "HTTPHandler.hpp"
#include "HTTPReply.hpp"
#include "InvalidHTTPVersionException.hpp"
#include "URIDecoder.hpp"

namespace exceptions = AxxonsoftInternProject::http::exceptions;
namespace stock = AxxonsoftInternProject::http::stock;

using std::shared_ptr,
	  std::dynamic_pointer_cast,
	  std::filesystem::directory_iterator,
	  std::ifstream,
	  AxxonsoftInternProject::http::URIDecoder,
	  AxxonsoftInternProject::http::DecoderStatus,
	  exceptions::InvalidHTTPVersionException;

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPRequestHandler : public HTTPHandler
		{
		private: 
			URIDecoder decoder;
			Target URITarget;

		private: 
			void VerifyVersion() override;
			void VerifyMethod();
			void HandleHeaders();
			void PutDirectoryContentToReplyBody();
			void PutFileToReplyBody(ifstream &sendedFile);
			void HandleGetFileMethod();
			void HandleGETContentMethod();
			void HandleGETMethod();
			
		public:
			HTTPRequestHandler(shared_ptr<HTTPRequest> handledDocument, shared_ptr<HTTPReply> outputDocument);

			void Handle() override;

			//void VerifyURL();
		};
	}
}