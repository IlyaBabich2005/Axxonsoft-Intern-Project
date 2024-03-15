#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>

#include <boost/exception/exception.hpp>
#include <boost/exception/diagnostic_information.hpp>include <boost/exception/diagnostic_information.hpp>

#include "HTTPRequest.hpp"
#include "Stock.hpp"
#include "command.hpp"
#include "nlohmann/json.hpp"
#include "InvalidTargetFormatException.hpp"
#include "NoFileToPostException.hpp"
#include "CantOpenPostedFileException.hpp"
#include "Config.hpp"

namespace AxxonsoftInternProject
{
	namespace Client
	{
		class CommandHandler
		{
		private: 
			std::shared_ptr<AxxonsoftInternProject::http::HTTPRequest> m_outputRequest;
			Command m_comand;
			nlohmann::json m_requestBody;

		private: 
			void setRequestUriAndMethod(
				const std::string& method, 
				const std::string& uri, 
				const AxxonsoftInternProject::http::ClientRequestType& type);
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
			CommandHandler(std::shared_ptr<AxxonsoftInternProject::http::HTTPRequest> outputReques);
			void Handle(Command comand);
		};
	}
}