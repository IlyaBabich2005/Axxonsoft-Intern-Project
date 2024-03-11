#include "InvalidTargetFormatException.hpp"

namespace AxxonsoftInternProject
{
	namespace Client
	{
		InvalidTargetException::what()
		{
			return "Invalid target format";
		}
	}
}