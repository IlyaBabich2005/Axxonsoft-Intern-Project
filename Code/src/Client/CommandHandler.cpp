#include "CommandHandler.hpp"

namespace AxxonsoftInternProject
{
	namespace Client
	{
		CommandHandler::CommandHandler(shared_ptr<HTTPRequest> outputRequest) :
			outputRequest{ outputRequest }
		{

		}

		void CommandHandler::SetHeaders()
		{
			if (this->outputRequest->body.size() != 0)
			{
				this->outputRequest->headers.push_back(http::HTTPHeader{ "Content-Length", std::to_string(this->outputRequest->body.size()) });
			}
		}

		void CommandHandler::ExtructTargetIntoRequestBody(string target)
		{
			string temp;
			string path = "";
			bool isFilename = false;
			this->requestBody["path"] = "";
			this->requestBody["filename"] = "";

			for (auto character : target)
			{
				if (character == '/')
				{
					if (isFilename)
					{
						std::cout << "Invalid Target format\n";
						throw new _exception;
					}
					else
					{
						path += temp;
						temp = "";
					}
				}
				else if (character == '.')
				{
					isFilename = true;
				}

				temp.push_back(character);
			}

			if (isFilename)
			{
				this->requestBody["filename"] = temp;
			}
			else
			{
				path += temp;
			}

			this->requestBody["path"] = path;
		}

		void CommandHandler::PutFileDataInRequestBody(std::ifstream& file)
		{
			auto end = file.tellg();
			file.seekg(0, std::ios::beg);

			auto size = std::size_t(end - file.tellg());
			vector<std::byte> buffer(size);

			file.read((char*)buffer.data(), buffer.size());

			this->requestBody["data"] = buffer;
			file.close();
		}

		void CommandHandler::HandlePostCommand()
		{
			this->outputRequest->method = "POST";
			std::ifstream file("./files/" + this->comand.targer, std::ios::binary | std::ios::ate);
			string filePath;
			string filename;

			if (file.is_open())
			{
				this->PutFileDataInRequestBody(file);

				std::cout << "Input file path on server: \n";

				if (std::getline(std::cin, filePath))
				{
					this->requestBody["path"] = filePath;
				}

				std::cout << "Input file name on server: \n";

				if (std::getline(std::cin, filename))
				{
					this->requestBody["filename"] = filename;
				}

				this->outputRequest->type = http::ClientRequestType::sendTarget;
			}
			else
			{
				std::cout << "No file to post\n";
				file.close();
				throw new _exception;
			}
		}

		void CommandHandler::HandleGetCommand()
		{
			this->outputRequest->method = "GET";
			this->outputRequest->uri = "/";

			this->outputRequest->type = http::ClientRequestType::downloadTarget;
		}

		void CommandHandler::HandleLSCommand()
		{
			this->outputRequest->method = "GET";
			this->outputRequest->uri = "/content";

			this->outputRequest->type = http::ClientRequestType::checkTarget;
		}

		void CommandHandler::HandleDeleteCommand()
		{
			this->outputRequest->method = "DELETE";
			this->outputRequest->uri = "/";

			this->outputRequest->type = http::ClientRequestType::deleteTarget;
		}

		void CommandHandler::HandleCommand()
		{
			try
			{
				if (this->comand.command != "post")
				{
					this->ExtructTargetIntoRequestBody(this->comand.targer);

					if (this->comand.command == "ls")
					{
						this->HandleLSCommand();
					}
					else if (this->comand.command == "get")
					{
						this->HandleGetCommand();
					}
					else if(this->comand.command == "delete")
					{
						this->HandleDeleteCommand();
					}
					else
					{
						std::cout << "Invalid Method\n";
					}
				}
				else
				{
					this->HandlePostCommand();
				}
			}
			catch (...)
			{
				std::cout << "Invalid command\n";
			}
		}

		void CommandHandler::Handle(Command command)
		{
			this->comand = command;

			this->outputRequest->version = "HTTP/1.0";
			this->HandleCommand();
			this->outputRequest->body = this->requestBody.dump(4);
			this->SetHeaders();
		}
	}
}