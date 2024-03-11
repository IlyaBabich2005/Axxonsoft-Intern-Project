#pragma once

#include <string>

namespace AxxonsoftInternProject
{
	namespace http
	{
		namespace stock
		{
			namespace characters
			{
				namespace separators
				{
					const std::string g_whiteSpaceSeparator = " ";
					const std::string g_headerNameValueSeparator = ": ";
					const std::string g_httpDocumentLineSeparator = "\r\n";
				}
			}

			namespace replyStatuses
			{
				const std::string g_badRequest { "400 BadRequest" };
				const std::string g_ok{ "200 OK" };
				const std::string g_notFound{ "404 Not Found" };
				const std::string g_methodNotAllowed{ "405 Method Not Allowed" };
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
				}

				namespace values
				{
					const std::string g_keepAlive{ "keep-alive" };
				}
			}

			namespace uri
			{
				namespace components
				{
					const std::string g_content{ "content" };
				}
			}
		}
	}
}