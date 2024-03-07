#pragma once

#include "HTTPSerializer.hpp"
#include "HTTPReply.hpp"

using std::dynamic_pointer_cast,
	  std::begin,
	  std::end,
	  stock::characters::separators::g_whiteSpaceSeparator;

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPReplySerializer : public HTTPSerializer
		{
		public:
			vector<const_buffer> Serialize(shared_ptr<HTTPDocument> document) override;
		};
	}
}