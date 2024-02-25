#pragma once

#include "HTTPDocument.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		const string requestMethods[]
		{
			"GET",
			"POST",
			"DELETE"
		};

		struct HTTPRequest : HTTPDocument
		{
			string method;
			string uri;
		
		private: 
			vector<const_buffer> SerializeVersion() override;
		};
	}
}