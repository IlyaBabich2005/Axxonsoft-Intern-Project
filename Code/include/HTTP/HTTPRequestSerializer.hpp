#pragma once

#include "HTTPSerializer.hpp"
#include "HTTPRequest.hpp"

using std::dynamic_pointer_cast,
std::begin,
std::end,
stock::characters::separators::whiteSpaceSeparator;


namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPRequestSerializer : HTTPSerializer
		{
		public:
			vector<const_buffer> Serialize(shared_ptr<HTTPDocument> document) override;
		};
	}
}