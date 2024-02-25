#pragma once

#include "HTTPDocument.hpp"

using separators::whiteSpaceSeparator;

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPReply : HTTPDocument
		{
		public:
			string code;
			string status;

        public:
			HTTPReply();

            vector<const_buffer> Serialize() override;
		};
	}
}