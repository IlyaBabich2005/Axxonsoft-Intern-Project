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
			std::string temp = "";
			std::string path = "";
			bool isFilename = false;
			requestBody[stock::json::g_pathFileldName] = "";
			requestBody[stock::json::g_filenameFiledName] = "";

			for (auto character : target)
			{
				if (character == '/')
				{
					if (isFilename)
					{
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
				requestBody[stock::json::g_pathFileldName] = temp;
			}
			else
			{
				path += temp;
			}

			requestBody[stock::json::g_pathFileldName] = path;
		}

		void CommandHandler::putFileDataInRequestBody(std::ifstream& file)
		{
			auto end = file.tellg();
			file.seekg(0, std::ios::beg);

			auto size = size_t(end - file.tellg());
			std::vector<std::byte> buffer(size);

			file.read((char*)buffer.data(), buffer.size());

			requestBody[stock::json::g_dataFieldName] = buffer;
		}

		void CommandHandler::getFileData(std::ifstream& file)
		{
			std::string filePath;
			std::string filename;

			putFileDataInRequestBody(file);

			std::cout << stock::messages::g_inputFilePathOnServer << "\n";

			if (std::getline(std::cin, filePath))
			{
				requestBody[stock::json::g_pathFileldName] = filePath;
			}

			std::cout << stock::messages::g_inputFileNameOnServer << "\n";

			if (std::getline(std::cin, filename))
			{
				requestBody[stock::json::g_filenameFiledName] = filename;
			}
		}

		void CommandHandler::handlePostCommand()
		{
			setRequestUriAndMethod(requestMethods::g_POST, stock::uri::g_empty, http::ClientRequestType::sendTarget);
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
					file.close();
					throw new Client::CantOpenPostedFileException;
				}
			}
			else
			{
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
			setRequestUriAndMethod(requestMethods::g_GET, stock::uri::g_empty, http::ClientRequestType::downloadTarget);
		}

		void CommandHandler::handleLSCommand()
		{
			setRequestUriAndMethod(requestMethods::g_GET, stock::uri::g_getContent, http::ClientRequestType::checkTarget);
		}

		void CommandHandler::handleDeleteCommand()
		{
			setRequestUriAndMethod(requestMethods::g_DELETE, stock::uri::g_empty, http::ClientRequestType::deleteTarget);
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
						std::cout << stock::messages::g_invalidMethod << "\n";
					}
				}
				else
				{
					handlePostCommand();
				}
			}
			catch (std::exception& ex)
			{
				std::cout << ex.what() << "\n";
			}
			catch (boost::exception& ex)
			{
				std::cout << boost::diagnostic_information(ex) << "\n";
			}
		}

		void CommandHandler::Handle(Command command)
		{
			this->comand = command;

			this->outputRequest->version = config::g_httpVersion;
			this->handleCommand();
			this->outputRequest->body = this->requestBody.dump(4);
			this->setHeaders();
		}
	}
}