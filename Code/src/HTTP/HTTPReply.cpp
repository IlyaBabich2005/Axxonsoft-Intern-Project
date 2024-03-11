#include "HTTPReply.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		HTTPReply::HTTPReply()
		{

		}

		HTTPReply::HTTPReply(std::string version, std::string status) : 
			HTTPDocument{ version },
			status{status}
		{

		}
	}
}