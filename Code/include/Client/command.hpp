#pragma once

#include <string>

using std::string;

namespace AxxonsoftInternProject
{
	namespace Client
	{
		const string commands[] =
		{
			"ls",
			"get",
			"post",
			"delete"
		};

		struct Command
		{
			string command;
			string targer;
		};
	}
}
