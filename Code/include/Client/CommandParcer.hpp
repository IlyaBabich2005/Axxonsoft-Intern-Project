#pragma once

#include "HTTPParser.hpp"
#include "command.hpp"
#include "checks.hpp"

namespace checks = AxxonsoftInternProject::checks::characters;
namespace http = AxxonsoftInternProject::http;

namespace AxxonsoftInternProject
{
	namespace Client
	{
		class CommandParcer
		{
		public:
			http::ParsingStatus Parce(std::shared_ptr<Command> parcingResult, std::string sourceCommand);
		};
	}
}