#include "CantOpenPostedFileException.hpp"

namespace AxxonsoftInternProject
{
	namespace Client
	{
		char* CantOpenPostedFileException::what()
		{
			return "Cant open posted file";
		}
	}
}