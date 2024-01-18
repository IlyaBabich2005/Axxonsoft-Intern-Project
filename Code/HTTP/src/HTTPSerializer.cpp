#include "HTTPSerializer.hpp"

namespace http
{
    SerializationStatus HTTPSerializer::GetStage()
    {
        return this->status;
    }

    void HTTPSerializer::SetStatus(SerializationStatus state)
    {
        this->status = status;
    }

    void HTTPSerializer::SetStage(SerializationStage stage)
    {
        this->stage = stage;
    }

    bool HTTPSerializer::IsDigid(char symbol)
    {
        return symbol >= '0' and symbol <= '9';
    }

    bool HTTPSerializer::IsChar(char symbol) 
    {
        return symbol >= 0 and symbol <= 127;
    }

    bool HTTPSerializer::IsControlChar(char symbol)
    {
        return symbol >= 0 and symbol <= 31 or symbol == 127;
    }

    bool HTTPSerializer::IsSpesialChar(char symbol)
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
