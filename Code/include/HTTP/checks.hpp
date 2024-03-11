#pragma once

namespace AxxonsoftInternProject
{
	namespace checks
	{
		namespace characters
		{
			const char spesialCharacters[]
			{
			'(', ')', '<', '>', '@',
			',', ';', ':', '\\', '"',
			'/', '[', ']', '?', '=',
			'{', '}', ' ', '\t',
			};

			const int g_firestCharacterCode{ 0 };
			const int g_lastCharacterCode{ 127 };
			const int g_lastControlCharCharacterCode{ 31 };

			bool IsDigid(char symbol);
			bool IsChar(char symbol);
			bool IsControlChar(char symbol);
			bool IsSpesialChar(char symbol);
		}
	}
}