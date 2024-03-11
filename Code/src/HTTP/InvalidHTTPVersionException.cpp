#include "InvalidHTTPVersionException.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		namespace exceptions
		{
			InvalidHTTPVersionException::what()
			{
				return "Invalid http version format";
			}
		}
	}
}