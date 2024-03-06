#pragma once

#include "HTTPParser.hpp"
#include "command.hpp"
#include "checks.hpp"

namespace checks = AxxonsoftInternProject::checks::characters;

using AxxonsoftInternProject::http::ParsingStatus;

namespace AxxonsoftInternProject
{
	namespace Client
	{
		class CommandParcer
		{
		public:
			ParsingStatus Parce(shared_ptr<Command> parcingResult, string sourceCommand);
		};
	}
}