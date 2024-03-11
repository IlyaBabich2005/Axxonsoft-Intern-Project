#include "NoFileToPostException.hpp"

namespace AxxonsoftInternProject
{
	namespace Client
	{
		char* NoFileToPostException::what()
		{
			return "No file to post";
		}
	}
}