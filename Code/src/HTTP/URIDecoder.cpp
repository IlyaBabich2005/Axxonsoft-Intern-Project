#pragma once

#include "URIDecoder.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		DecoderStatus URIDecoder::Decode(string uri, Target& targer)
		{
			string temp;

			for (auto character : uri)
			{
				if (IsControlChar(character) || IsSpesialChar(character))
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