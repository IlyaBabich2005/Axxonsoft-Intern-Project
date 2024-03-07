#pragma once

#include <exception>

using std::exception;

namespace AxxonsoftInternProject
{
	namespace Client
	{
		class NoFileToPostException : exception
		{
		};
	}

}