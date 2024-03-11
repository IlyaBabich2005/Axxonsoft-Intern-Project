#pragma once

#include <exception>

namespace AxxonsoftInternProject
{
	namespace http
	{
		namespace exceptions
		{
			class InvalidHTTPVersionException : public std::exception
			{
			};
		}
	}
}