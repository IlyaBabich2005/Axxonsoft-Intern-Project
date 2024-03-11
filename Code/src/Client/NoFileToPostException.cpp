#include "NoFileToPostException.hpp"

namespace AxxonsoftInternProject
{
	namespace Client
	{
		NoFileToPostException::what()
		{
			return "No file to post";
		}
	}
}