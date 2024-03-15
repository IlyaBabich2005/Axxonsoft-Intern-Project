#pragma once

#include "URIDecoder.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		DecoderStatus URIDecoder::Decode(std::string uri, Target& targer)
		{
			std::string temp;

			for (auto character : uri)
			{
				if (AxxonsoftInternProject::checks::characters::IsControlChar(character) || 
					AxxonsoftInternProject::checks::characters::IsSpesialChar(character))
				{
					if (character == '/' && !targer.isFile)
					{
						if (temp != "")
						{
							targer.components.push_back(temp);
							temp = "";
						}
						
						continue;
					}
					else
					{
						return badURI;
					}
				}
				else if(character == '.')
				{	
					targer.isFile = true;
				}
				temp.push_back(character);
			}

			if (temp != "")
			{
				targer.components.push_back(temp);
			}

			return goodURI;
		}
	}
}