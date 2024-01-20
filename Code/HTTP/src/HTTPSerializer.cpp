#include "HTTPSerializer.hpp"

namespace http
{
    HTTPSerializer::HTTPSerializer(HTTPDocument* document) :
        document{document}
    {
    }

    HTTPSerializer::~HTTPSerializer()
    {
        delete this->document;
    }

    SerializationStatus HTTPSerializer::GetStage()
    {
        return this->status;
    }

    HTTPDocument* HTTPSerializer::GetDocument()
    {
        return this->document;
    }

    void HTTPSerializer::SetStatus(SerializationStatus state)
    {
        this->status = status;
    }

    void HTTPSerializer::SetStage(SerializationStage stage)
    {
        this->stage = stage;
    }

    SerializationStatus HTTPSerializer::HandleSymbol(char curentSymbol)
    {
        switch (this->stage)
        {
            case httpVersion: this->HandleVersionSymbol(curentSymbol); break;

        }
    }

    void HTTPSerializer::HandleVersionSymbol(char curentSymbol)
    {
        if (curentSymbol == '\r')
        {
            this->SetStage(SerializationStage::expecting_newline_1);
        }
        else if (!IsChar(curentSymbol) || IsControlChar(curentSymbol) || IsSpesialChar(curentSymbol))
        {
            this->SetStatus(SerializationStatus::endResultBad);
        }
        else
        {
            this->document->version.push_back(curentSymbol);
        }
    }
}
