#pragma once

#include <exception>

namespace AxxonsoftInternProject
{
	namespace Client
	{
		class CantOpenPostedFileException : std::exception
		{
		public:
			char* what();
		};
	}

}