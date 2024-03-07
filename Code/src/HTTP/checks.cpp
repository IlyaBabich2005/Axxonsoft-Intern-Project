#include "checks.hpp"

namespace AxxonsoftInternProject
{
    bool checks::characters::IsDigid(char symbol)
    {
        return symbol >= '0' && symbol <= '9';
    }

    bool checks::characters::IsChar(char symbol)
    {
        int firestCharacterCode = 0;
        int lastCharacterCode = 127;

        return symbol >= firestCharacterCode && symbol <= lastCharacterCode;
    }

    bool checks::characters::IsControlChar(char symbol)
    {
        int firestCharacterCode = 0;
        int lastCharacterCode = 127;
        int lastControlCharCharacterCode = 31;

        return symbol >= firestCharacterCode && symbol <= lastControlCharCharacterCode || symbol == lastCharacterCode;
    }

    bool checks::characters::IsSpesialChar(char symbol)
    {
        for (auto specialSymbol : spesialCharacters)
        {
            if (symbol == specialSymbol)
            {
                return true;
            }
        }

        return false;
    }
}