#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>

#include "HTTPRequest.hpp"
#include "Stock.hpp"
#include "command.hpp"
#include "nlohmann/json.hpp"
#include "InvalidTargetFormatException.hpp"
#include "NoFileToPostException.hpp"
#include "CantOpenPostedFileException.hpp"

namespace http = AxxonsoftInternProject::http;
namespace stock = AxxonsoftInternProject::http::stock;
namespace headers = stock::headers;
namespace requestMethods = stock::requestMethods;
namespace clientCommands = stock::clientCommands;
namespace Client = AxxonsoftInternProject::Client;
namespace filesystem = std::filesystem;

namespace AxxonsoftInternProject
{
	namespace Client
	{
		class CommandHandler
		{
		private: 
			std::shared_ptr<http::HTTPRequest> outputRequest;
			Command comand;
			nlohmann::json requestBody;

		private: 
			void setRequestUriAndMethod(const std::string& method, const std::string& uri, const http::ClientRequestType& type);
			void setHeaders();
			void putFileDataInRequestBody(std::ifstream& file);
			void extructTargetIntoRequestBody(std::string target);
			void getFileData(std::ifstream& file);
			void handleDeleteCommand();
			void handleLSCommand();
			void handleGetCommand();
			void handlePostCommand();
			void handleCommand();

		public:
			CommandHandler(std::shared_ptr<http::HTTPRequest> outputReques);
			void Handle(Command comand);
		};
	}
}