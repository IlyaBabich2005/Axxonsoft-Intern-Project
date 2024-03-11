#include "CommandHandler.hpp"

namespace AxxonsoftInternProject
{
	namespace Client
	{
		CommandHandler::CommandHandler(std::shared_ptr<http::HTTPRequest> outputRequest) :
			outputRequest{ outputRequest }
		{

		}

		void CommandHandler::setHeaders()
		{
			if (outputRequest->body.size() != 0)
			{
				outputRequest->headers.push_back(http::HTTPHeader{ headers::names::g_contentLength, std::to_string(outputRequest->body.size()) });
			}
		}

		void CommandHandler::extructTargetIntoRequestBody(std::string target)
		{
			std::string temp;
			std::string path = "";
			bool isFilename = false;
			requestBody["path"] = "";
			requestBody["filename"] = "";

			for (auto character : target)
			{
				if (character == '/')
				{
					if (isFilename)
					{
						std::cout << "Invalid Target format\n";
						throw new Client::InvalidTargetException;
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
				requestBody["filename"] = temp;
			}
			else
			{
				path += temp;
			}

			requestBody["path"] = path;
		}

		void CommandHandler::putFileDataInRequestBody(std::ifstream& file)
		{
			auto end = file.tellg();
			file.seekg(0, std::ios::beg);

			auto size = size_t(end - file.tellg());
			std::vector<std::byte> buffer(size);

			file.read((char*)buffer.data(), buffer.size());

			requestBody["data"] = buffer;
		}

		void CommandHandler::getFileData(std::ifstream& file)
		{
			std::string filePath;
			std::string filename;

			putFileDataInRequestBody(file);

			std::cout << "Input file path on server: \n";

			if (std::getline(std::cin, filePath))
			{
				requestBody["path"] = filePath;
			}

			std::cout << "Input file name on server: \n";

			if (std::getline(std::cin, filename))
			{
				requestBody["filename"] = filename;
			}
		}

		void CommandHandler::handlePostCommand()
		{
			setRequestUriAndMethod(requestMethods::g_POST, "/", http::ClientRequestType::sendTarget);
			std::string pathToPostedFile = comand.targer;

			if (filesystem::exists(pathToPostedFile))
			{
				std::ifstream file(pathToPostedFile, std::ios::binary | std::ios::ate);

				if (file.is_open())
				{
					getFileData(file);

					file.close();
				}
				else
				{
					std::cout << "Cant open posted file\n";
					file.close();
					throw new Client::CantOpenPostedFileException;
				}
			}
			else
			{
				std::cout << "Cant open posted file\n";
				throw new Client::NoFileToPostException;
			}
		}

		void CommandHandler::setRequestUriAndMethod(const std::string& method, const std::string& uri, const http::ClientRequestType& type)
		{
			outputRequest->method = method;
			outputRequest->uri = uri;
			outputRequest->type = type;
		}

		void CommandHandler::handleGetCommand()
		{
			setRequestUriAndMethod(requestMethods::g_GET, "/", http::ClientRequestType::downloadTarget);
		}

		void CommandHandler::handleLSCommand()
		{
			setRequestUriAndMethod(requestMethods::g_GET, "/content", http::ClientRequestType::checkTarget);
		}

		void CommandHandler::handleDeleteCommand()
		{
			setRequestUriAndMethod(requestMethods::g_DELETE, "/content", http::ClientRequestType::deleteTarget);
		}

		void CommandHandler::handleCommand()
		{
			try
			{
				if (this->comand.command != clientCommands::g_post)
				{
					this->extructTargetIntoRequestBody(this->comand.targer);

					if (this->comand.command == clientCommands::g_ls)
					{
						this->handleLSCommand();
					}
					else if (this->comand.command == clientCommands::g_get)
					{
						this->handleGetCommand();
					}
					else if(this->comand.command == clientCommands::g_delete)
					{
						this->handleDeleteCommand();
					}
					else
					{
						std::cout << "Invalid Method\n";
					}
				}
				else
				{
					handlePostCommand();
				}
			}
			catch (std::exception& ex)
			{
				std::cout << "Invalid command\n";
			}
		}

		void CommandHandler::Handle(Command command)
		{
			this->comand = command;

			this->outputRequest->version = "HTTP/1.0";
			this->handleCommand();
			this->outputRequest->body = this->requestBody.dump(4);
			this->setHeaders();
		}
	}
}