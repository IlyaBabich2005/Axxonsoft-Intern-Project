#pragma once

#include <string>

namespace AxxonsoftInternProject
{
	namespace SERVER
	{
		struct AuthPair 
		{
			std::string nonce;
			std::string opaque;
		};
	}
}