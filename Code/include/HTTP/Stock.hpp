#pragma once

#include <string>

using std::string;

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
					const string g_whiteSpaceSeparator = " ";
					const string g_headerNameValueSeparator = ": ";
					const string g_httpDocumentLineSeparator = "\r\n";
				}
			}

			namespace replyStatuses
			{
				const string g_badRequest { "400 BadRequest" };
				const string g_ok{ "200 OK" };
				const string g_notFound{ "404 Not Found" };
				const string g_methodNotAllowed{ "405 Method Not Allowed" };
			}


			namespace clientCommands
			{
				const string g_ls{ "ls" };
				const string g_get{ "get" };
				const string g_delete{ "delete" };
				const string g_post{ "post" };
			}

			namespace requestMethods
			{
				const string g_GET{ "GET" };
				const string g_POST{ "POST" };
				const string g_DELETE{ "DELETE" };
			}

			namespace headers
			{
				namespace names
				{
					const string g_connection{ "Connection" };
					const string g_contentLength{ "Content-Length" };
				}

				namespace values
				{
					const string g_keepAlive{ "keep-alive" };
				}
			}

			namespace uri
			{
				namespace components
				{
					const string g_content{ "content" };
				}
			}
		}
	}
}