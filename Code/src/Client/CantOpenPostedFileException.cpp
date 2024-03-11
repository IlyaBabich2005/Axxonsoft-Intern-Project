#include "CantOpenPostedFileException.hpp"

namespace AxxonsoftInternProject
{
	namespace Client
	{
		CantOpenPostedFileException::what()
		{
			return "Cant open posted file";
		}
	}
}