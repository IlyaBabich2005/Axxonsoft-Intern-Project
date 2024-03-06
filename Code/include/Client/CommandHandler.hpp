#pragma once

#include <fstream>
#include <iostream>

#include "HTTPRequest.hpp"
#include "command.hpp"
#include "nlohmann/json.hpp"

namespace http = AxxonsoftInternProject::http;

using std::shared_ptr,
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
			void SetHeaders();
			void PutFileDataInRequestBody(std::ifstream& file);
			void ExtructTargetIntoRequestBody(string target);
			void HandleDeleteCommand();
			void HandleLSCommand();
			void HandleGetCommand();
			void HandlePostCommand();
			void HandleCommand();

		public:
			CommandHandler(shared_ptr<HTTPRequest> outputReques);
			void Handle(Command comand);
		};
	}
}