#include "Stock.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		namespace stock
		{
			namespace functions
			{
				std::string generateRandomString(int size)
				{
					srand(time(NULL) + rand());

					std::string randomString;

					for (int i = 0; i < size; i++)
					{
						int randomChar = rand() % AxxonsoftInternProject::http::stock::characters::g_charsetForGenerator.size();

						randomString += AxxonsoftInternProject::http::stock::characters::g_charsetForGenerator[randomChar];
					}

					return randomString;
				}
			}
		}
	}
}