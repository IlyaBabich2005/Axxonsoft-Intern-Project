#pragma once

#include <string>

namespace AxxonsoftInternProject
{
	namespace Client
	{
		const std::string commands[] =
		{
			"ls",
			"get",
			"post",
			"delete"
		};

		struct Command
		{
			std::string command;
			std::string targer;
		};
	}
}
