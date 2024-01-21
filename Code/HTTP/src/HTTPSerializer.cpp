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
            case expectingHeaderNewline: this->HandleNewHeaderLineExpectingSymbol(curentSymbol); break;
        }
    }

    void HTTPSerializer::HandleVersionSymbol(char curentSymbol)
    {
        if (curentSymbol == '\r')
        {
            this->stage = SerializationStage::expectingHeaderNewline;
        }
        else if (!IsChar(curentSymbol) || IsControlChar(curentSymbol) || IsSpesialChar(curentSymbol))
        {
            this->status = SerializationStatus::endResultBad;
        }
        else
        {
            this->document->version.push_back(curentSymbol);
        }
    }

    void HTTPSerializer::HandleNewHeaderLineExpectingSymbol(char curentSymbol)
    {
        if (curentSymbol == '\n')
        {
            this->stage = SerializationStage::NewLineStart;
        }
        else
        {
            this->status = SerializationStatus::endResultBad;
        }
    }

    void HTTPSerializer::HandleNewLineStartSymbol(char curentSymbol)
    {
        if (curentSymbol == '\n')
        {
            this->stage = SerializationStage::expectingLineBeforeBody;
        }
        else if (!IsChar(curentSymbol) || IsControlChar(curentSymbol) || IsSpesialChar(curentSymbol))
        {
            this->status = SerializationStatus::endResultBad;
        }
        else
        {
            this->document->headers.push_back(HTTPHeader{});
            this->document->headers.back().name.push_back(curentSymbol);
            this->stage = SerializationStage::headerName;
        }
    }

    void HTTPSerializer::HandleHeaderNameSymbol(char curentSymbol)
    {
        if (curentSymbol == ':')
        {
            this->stage = SerializationStage::spaceBeforeHaderValue;
        }
        else if (!IsChar(curentSymbol) || IsControlChar(curentSymbol) || IsSpesialChar(curentSymbol))
        {
            this->status = SerializationStatus::endResultBad;
        }
        else
        {
            this->document->headers.back().name.push_back(curentSymbol);
        }
    }

    void HTTPSerializer::HandleSymbolBeforeHeaderValue(char curentSymbol)
    {
        if (curentSymbol == ' ')
        {
            this->stage = SerializationStage::headerValue;
        }
        else
        {
            this->status = SerializationStatus::endResultBad;
        }
    }

    void HTTPSerializer::HandleHeaderValueSymbol(char curentSymbol)
    {
        if (curentSymbol == '\r')
        {
            this->stage = SerializationStage::expectingHeaderNewline;
        }
        else if (!IsChar(curentSymbol) || IsControlChar(curentSymbol) || IsSpesialChar(curentSymbol))
        {
            this->status = SerializationStatus::endResultBad;
        }
        else
        {
            this->document->headers.back().name.push_back(curentSymbol);
        }
    }


}
