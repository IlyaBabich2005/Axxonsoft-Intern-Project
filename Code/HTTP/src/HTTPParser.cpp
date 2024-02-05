#include "HTTPParser.hpp"

namespace http
{
    HTTPParser::HTTPParser(HTTPDocument* document) :
        document{document},
        status{ParsingStatus::indeterminate}
    {
    }

    HTTPParser::~HTTPParser()
    {
        delete this->document;
    }

    ParsingStatus HTTPParser::GetStage()
    {
        return this->status;
    }

    HTTPDocument* HTTPParser::GetDocument()
    {
        return this->document;
    }

    void HTTPParser::SetStatus(ParsingStatus state)
    {
        this->status = status;
    }

    void HTTPParser::SetStage(ParsingStage stage)
    {
        this->stage = stage;
    }

    ParsingStatus HTTPParser::HandleSymbol(char curentSymbol)
    {
        switch (this->stage)
        {
            case httpVersion: this->HandleVersionSymbol(curentSymbol); break;
            case expectingHeaderNewLine: this->HandleNewHeaderLineExpectingSymbol(curentSymbol); break;
            case newLineStart: this->HandleNewLineStartSymbol(curentSymbol); break;
            case headerName: this->HandleHeaderNameSymbol(curentSymbol); break;
            case spaceBeforeHaderValue: this->HandleSymbolBeforeHeaderValue(curentSymbol); break;
            case headerValue: this->HandleHeaderValueSymbol(curentSymbol); break;
            case expectingLineBeforeBody: HandleBodyStartExpectingSymbol(curentSymbol); break;
            case body: this->HandleBodySymbol(curentSymbol); return;
        }
    }

    void HTTPParser::HandleNewHeaderLineExpectingSymbol(char curentSymbol)
    {
        if (curentSymbol == '\n')
        {
            this->stage = ParsingStage::newLineStart;
        }
        else
        {
            this->status = ParsingStatus::endResultBad;
        }
    }

    void HTTPParser::HandleNewLineStartSymbol(char curentSymbol)
    {
        if (curentSymbol == '\r')
        {
            this->stage = ParsingStage::expectingLineBeforeBody;
        }
        else if (!IsChar(curentSymbol) || IsControlChar(curentSymbol) || IsSpesialChar(curentSymbol))
        {
            this->status = ParsingStatus::endResultBad;
        }
        else
        {
            this->document->headers.push_back(HTTPHeader{});
            this->document->headers.back().name.push_back(curentSymbol);
            this->stage = ParsingStage::headerName;
        }
    }

    void HTTPParser::HandleHeaderNameSymbol(char curentSymbol)
    {
        if (curentSymbol == ':')
        {
            this->stage = ParsingStage::spaceBeforeHaderValue;
        }
        else if (!IsChar(curentSymbol) || IsControlChar(curentSymbol) || IsSpesialChar(curentSymbol))
        {
            this->status = ParsingStatus::endResultBad;
        }
        else
        {
            this->document->headers.back().name.push_back(curentSymbol);
        }
    }

    void HTTPParser::HandleSymbolBeforeHeaderValue(char curentSymbol)
    {
        if (curentSymbol == ' ')
        {
            this->stage = ParsingStage::headerValue;
        }
        else
        {
            this->status = ParsingStatus::endResultBad;
        }
    }

    void HTTPParser::HandleHeaderValueSymbol(char curentSymbol)
    {
        if (curentSymbol == '\r')
        {
            this->stage = ParsingStage::expectingHeaderNewLine;
        }
        else if (!IsChar(curentSymbol) || IsControlChar(curentSymbol) || IsSpesialChar(curentSymbol))
        {
            this->status = ParsingStatus::endResultBad;
        }
        else
        {
            this->document->headers.back().name.push_back(curentSymbol);
        }
    }

    void HTTPParser::HandleBodyStartExpectingSymbol(char curentSymbol)
    {
        if (curentSymbol == '\n')
        {
            this->stage = ParsingStage::body;
        }
        else
        {
            this->status = ParsingStatus::endResultBad;
        }

    }

    void HTTPParser::HandleBodySymbol(char curentSymbol)
    {
        this->document->body.push_back(curentSymbol);
    }
}
