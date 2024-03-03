#include "HTTPReply.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		HTTPReply::HTTPReply()
		{

		}

		HTTPReply::HTTPReply(string version, string status) : 
			HTTPDocument{ version },
			status{status}
		{

		}
	}
}