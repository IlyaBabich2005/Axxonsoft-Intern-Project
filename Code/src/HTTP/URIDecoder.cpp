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
						targer.components.push_back(temp);
						temp = "";
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
				else
				{
					temp.push_back(character);
				}
			}

			targer.components.push_back(temp);
			return goodURI;
		}
	}
}