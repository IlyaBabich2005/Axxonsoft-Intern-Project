#pragma once

#include <string>
#include <time.h>
#include <random>

namespace AxxonsoftInternProject
{
	namespace http
	{
		namespace stock
		{
			namespace characters
			{
				const std::string g_charsetForGenerator{ "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" };

				namespace separators
				{
					const std::string g_whiteSpaceSeparator{ " " };
					const std::string g_headerNameValueSeparator{ ": " };
					const std::string g_httpDocumentLineSeparator{ "\r\n" };
					const std::string g_httpHeaderValueArgumentsSeparator{ ", " };
					const std::string g_httpHeaderValueFieldSeparator{ "=" };
					const std::string g_httpHeaderValueSeparator{ "; " };
					const std::string g_doubleQuotes{ "\"" };
				}
			}

			namespace replyStatuses
			{
				const std::string g_badRequest{ "400 BadRequest" };
				const std::string g_ok{ "200 OK" };
				const std::string g_notFound{ "404 Not Found" };
				const std::string g_methodNotAllowed{ "405 Method Not Allowed" };
				const std::string g_unauthorized{ "401 Unauthorized" };
			}


			namespace clientCommands
			{
				const std::string g_ls{ "ls" };
				const std::string g_get{ "get" };
				const std::string g_delete{ "delete" };
				const std::string g_post{ "post" };
			}

			namespace requestMethods
			{
				const std::string g_GET{ "GET" };
				const std::string g_POST{ "POST" };
				const std::string g_DELETE{ "DELETE" };
			}

			namespace headers
			{
				namespace names
				{
					const std::string g_connection{ "Connection" };
					const std::string g_contentLength{ "Content-Length" };
					const std::string g_authorization{ "Authorization" };
					const std::string g_wwwAuthenticate{ "WWW-Authenticate" };
					const std::string g_host{ "Host" };
					const std::string g_cookie{ "Cookie" };
					const std::string g_setCookie{ "Set-Cookie" };
				}

				namespace values
				{
					const std::string g_keepAlive{ "keep-alive" };
					const std::string g_opaque{ "opaque" };
					const std::string g_digest{ "Digest" };
					const std::string g_nonce{ "nonce" };
					const std::string g_qop{ "qop" };
					const std::string g_auth{ "auth" };
					const std::string g_username{ "username" };
					const std::string g_response{ "response" };
					const std::string g_sessionID{ "sessionID" };
				}
			}

			namespace uri
			{
				namespace components
				{
					const std::string g_content{ "content" };
				}

				const std::string g_empty{ "/" };
				const std::string g_getContent{ "/content" };
			}

			namespace messages
			{
				const std::string g_cantConnect{ "Can't connect" };
				const std::string g_badCommand{ "Bad command" };
				const std::string g_writing{ "Writing..." };
				const std::string g_written{ "Written!" };
				const std::string g_parced{ "Parced" };
				const std::string g_parcedBad{ "Parced bad" };
				const std::string g_badReply{ "Bad reply" };
				const std::string g_parcedGood{ "Parced good" };
				const std::string g_parcingContinious{ "Parcing continious" };
				const std::string g_inputFilePathOnServer{ "Input file path on server: " };
				const std::string g_inputFileNameOnServer{ "Input file name on server: " };
				const std::string g_invalidMethod{ "Invalid Method" };
				const std::string g_targetWasSuccesfullyDownloaded{ "Target was succesfully downloaded" };
				const std::string g_targetWasSuccesfullyDeleted{ "Target was succesfully deleted" };
				const std::string g_targetWasSuccesfullySended{ "Target was succesfully sended" };
				const std::string g_clientRequestTypeError{ "Client request type error" };
				const std::string g_badRequest{ "Bad Request" };
				const std::string g_notFound{ "Not found" };
				const std::string g_handling{ "Handling" };
				const std::string g_directoryCreated{ "Directory created" };
				const std::string g_decoded{ "Decoded" };
				const std::string g_readed{ "Readed" };
				const std::string g_writedInFile{ "Writed in file" };
				const std::string g_openningFile{ "Openning file" };
				const std::string g_serializingBody{ "Serializing body" };
				const std::string g_succesfullyChecked{ "Succesfully checked" };
				const std::string g_scanDirectory{ "Scun directory" };
				const std::string g_searchFile{ "Search file" };
				const std::string g_inputLogin{ "Input login: " };
				const std::string g_inputPassword{ "Input password: " };
				const std::string g_authError{ "Auth error" };
				const std::string g_unauthorized{ "Unauthorized" };
			}

			namespace json
			{
				const int g_dumpSize{ 4 };
				const std::string g_pathFileldName{ "path" };
				const std::string g_filenameFiledName{ "filename" };
				const std::string g_dataFieldName{ "data" };
				const std::string g_contentFieldName{ "content" };
			}

			const std::string g_httpVersionHead{ "HTTP/" };

			const std::string g_httpVersions[]
			{
				"HTTP/1.0"
			};

			namespace functions
			{
				std::string generateRandomString(int size);
			}
		}
	}
}