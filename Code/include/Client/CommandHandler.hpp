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
namespace Client = AxxonsoftInternProject::Client;

using stock::headers::names::g_contentLength,
	  stock::requestMethods::g_GET,
	  stock::requestMethods::g_DELETE,
	  stock::requestMethods::g_POST,
	  stock::clientCommands::g_delete,
	  stock::clientCommands::g_post,
	  stock::clientCommands::g_ls,
	  stock::clientCommands::g_get,
	  Client::NoFileToPostException,
	  Client::InvalidTargetException,
	  Client::CantOpenPostedFileException,
	  std::filesystem::exists,
	  std::shared_ptr,
	  std::ifstream,
	  std::ios,
	  std::byte,
	  std::cout,
	  http::ClientRequestType,
	  http::HTTPRequest;

namespace AxxonsoftInternProject
{
	namespace Client
	{
		class CommandHandler
		{
		private: 
			shared_ptr<HTTPRequest> outputRequest;
			Command comand;
			json requestBody;

		private: 
			void setRequestUriAndMethod(const string& method, const string& uri, const ClientRequestType& type);
			void setHeaders();
			void putFileDataInRequestBody(std::ifstream& file);
			void extructTargetIntoRequestBody(string target);
			void getFileData(ifstream& file);
			void handleDeleteCommand();
			void handleLSCommand();
			void handleGetCommand();
			void handlePostCommand();
			void handleCommand();

		public:
			CommandHandler(shared_ptr<HTTPRequest> outputReques);
			void Handle(Command comand);
		};
	}
}