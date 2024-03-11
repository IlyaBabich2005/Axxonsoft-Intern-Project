#pragma once

#include "Target.hpp"
#include "checks.hpp"

namespace charChecks = AxxonsoftInternProject::checks::characters;

namespace AxxonsoftInternProject
{
	namespace http
	{
		enum DecoderStatus
		{
			badURI = 0,
			goodURI
		};

		class URIDecoder
		{
		public:
			DecoderStatus Decode(std::string uri, Target& targer);
		};
	}
}