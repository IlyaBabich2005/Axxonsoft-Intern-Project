#pragma once

#include <exception>

namespace AxxonsoftInternProject
{
	namespace Client
	{
		class NoFileToPostException : std::exception
		{
		public:
			char* what();
		};
	}

}