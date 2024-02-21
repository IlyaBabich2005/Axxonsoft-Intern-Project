#pragma once

#include <exception>

using std::exception;

namespace AxxonsoftInternProject
{
	namespace http
	{
		namespace exceptions
		{
			class InvalidHTTPVersionException : exception
			{
			};
		}
	}
}