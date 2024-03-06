#include "CommandParcer.hpp"

namespace AxxonsoftInternProject
{
	namespace Client
	{
		ParsingStatus CommandParcer::Parce(shared_ptr<Command> parcingResult, string sourceCommand)
		{
			bool isTargetParcing = false;

			for (auto symbol : sourceCommand)
			{
				if (checks::characters::IsChar(symbol) && !checks::characters::IsControlChar(symbol))
				{
					if (!isTargetParcing)
					{
						if(symbol == ' ')
						{
							isTargetParcing = true;
						}
						else
						{
							parcingResult->command.push_back(symbol);
						}
					}
					else
					{
						parcingResult->targer.push_back(symbol);
					}
				}
				else
				{
					return ParsingStatus::endResultBad;
				}
			}

			return ParsingStatus::endResultGood;
		}
	}
}