#include "InvalidTargetFormatException.hpp"

namespace AxxonsoftInternProject
{
	namespace Client
	{
		char* InvalidTargetException::what()
		{
			return "Invalid target format";
		}
	}
}