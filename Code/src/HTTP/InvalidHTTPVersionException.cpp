#include "InvalidHTTPVersionException.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		namespace exceptions
		{
			char* InvalidHTTPVersionException::what()
			{
				return "Invalid http version format";
			}
		}
	}
}