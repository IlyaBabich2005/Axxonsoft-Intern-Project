#pragma once

#include "Target.hpp"
#include "checks.hpp"

using AxxonsoftInternProject::checks::characters::IsControlChar,
	  AxxonsoftInternProject::checks::characters::IsSpesialChar,
	  AxxonsoftInternProject::http::Target;

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
			DecoderStatus Decode(string uri, Target& targer);
		};
	}
}