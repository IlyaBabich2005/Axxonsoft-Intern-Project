#include "CommandHandler.hpp"

namespace AxxonsoftInternProject
{
	namespace Client
	{
		CommandHandler::CommandHandler(shared_ptr<HTTPRequest> outputRequest) :
			outputRequest{ outputRequest }
		{

		}

		void CommandHandler::setHeaders()
		{
			if (outputRequest->body.size() != 0)
			{
				outputRequest->headers.push_back(http::HTTPHeader{ g_contentLength, std::to_string(outputRequest->body.size()) });
			}
		}

		void CommandHandler::extructTargetIntoRequestBody(string target)
		{
			string temp;
			string path = "";
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
						throw new InvalidTargetException;
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
			file.seekg(0, ios::beg);

			auto size = size_t(end - file.tellg());
			vector<byte> buffer(size);

			file.read((char*)buffer.data(), buffer.size());

			requestBody["data"] = buffer;
		}

		void CommandHandler::getFileData(ifstream& file)
		{
			string filePath;
			string filename;

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
			setRequestUriAndMethod(g_POST, "/", ClientRequestType::sendTarget);
			string pathToPostedFile = comand.targer;

			if (exists(pathToPostedFile))
			{
				ifstream file(pathToPostedFile, ios::binary | ios::ate);

				if (file.is_open())
				{
					getFileData(file);

					file.close();
				}
				else
				{
					cout << "Cant open posted file\n";
					file.close();
					throw new CantOpenPostedFileException;
				}
			}
			else
			{
				cout << "Cant open posted file\n";
				throw new NoFileToPostException;
			}
		}

		void CommandHandler::setRequestUriAndMethod(const string& method, const string& uri, const ClientRequestType& type)
		{
			outputRequest->method = method;
			outputRequest->uri = uri;
			outputRequest->type = type;
		}

		void CommandHandler::handleGetCommand()
		{
			setRequestUriAndMethod(g_GET, "/", ClientRequestType::downloadTarget);
		}

		void CommandHandler::handleLSCommand()
		{
			setRequestUriAndMethod(g_GET, "/content", ClientRequestType::checkTarget);
		}

		void CommandHandler::handleDeleteCommand()
		{
			setRequestUriAndMethod(g_DELETE, "/content", ClientRequestType::deleteTarget);
		}

		void CommandHandler::handleCommand()
		{
			try
			{
				if (this->comand.command != g_post)
				{
					this->extructTargetIntoRequestBody(this->comand.targer);

					if (this->comand.command == g_ls)
					{
						this->handleLSCommand();
					}
					else if (this->comand.command == g_get)
					{
						this->handleGetCommand();
					}
					else if(this->comand.command == g_delete)
					{
						this->handleDeleteCommand();
					}
					else
					{
						cout << "Invalid Method\n";
					}
				}
				else
				{
					handlePostCommand();
				}
			}
			catch (exception& ex)
			{
				cout << "Invalid command\n";
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