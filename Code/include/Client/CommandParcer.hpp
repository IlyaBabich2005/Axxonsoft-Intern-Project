#pragma once

#include "HTTPParser.hpp"
#include "command.hpp"
#include "checks.hpp"

namespace AxxonsoftInternProject
{
	namespace Client
	{
		class CommandParcer
		{
		public:
			AxxonsoftInternProject::http::ParsingStatus Parce(std::shared_ptr<Command> parcingResult, std::string sourceCommand);
		};
	}
}