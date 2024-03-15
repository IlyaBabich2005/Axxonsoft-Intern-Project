#include "CommandParcer.hpp"

namespace AxxonsoftInternProject
{
	namespace Client
	{
		http::ParsingStatus CommandParcer::Parce(std::shared_ptr<Command> parcingResult, std::string sourceCommand)
		{
			bool isTargetParcing = false;

			for (auto symbol : sourceCommand)
			{
				if (checks::characters::IsChar(symbol) && !checks::characters::IsControlChar(symbol))
				{
					if (!isTargetParcing)
					{
						if (symbol == ' ')
						{
							isTargetParcing = true;
						}
						else
						{
							parcingResult->m_command.push_back(symbol);
						}
					}
					else
					{
						parcingResult->m_targer.push_back(symbol);
					}
				}
				else
				{
					return http::ParsingStatus::endResultBad;
				}
			}

			return http::ParsingStatus::endResultGood;
		}
	}
}