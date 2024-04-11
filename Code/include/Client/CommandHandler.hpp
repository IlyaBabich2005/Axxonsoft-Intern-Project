#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>

#include <boost/exception/exception.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/format.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>

#include "HTTPRequest.hpp"
#include "Stock.hpp"
#include "command.hpp"
#include "nlohmann/json.hpp"
#include "InvalidTargetFormatException.hpp"
#include "NoFileToPostException.hpp"
#include "CantOpenPostedFileException.hpp"
#include "Config.hpp"
#include "LoginManager.hpp"

namespace AxxonsoftInternProject
{
	namespace Client
	{
		enum HandlingResult
		{
			Success = 0,
			Error
		};

		class CommandHandler
		{
		private: 
			std::shared_ptr<AxxonsoftInternProject::http::HTTPRequest> m_outputRequest;
			Command m_comand;
			nlohmann::json m_requestBody;
			std::shared_ptr<LoginManager> m_loginManager;
			HandlingResult m_handlingResult;

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
			void formAuthHeader();
			std::string formRequestSring();
			void formCookie();

		public:
			CommandHandler();
			CommandHandler(std::shared_ptr<LoginManager> loginManager);
			HandlingResult Handle(Command comand, std::shared_ptr<http::HTTPRequest> request);
		};
	}
}