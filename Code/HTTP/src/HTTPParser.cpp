#include "HTTPParser.hpp"

namespace AxxonsoftInternProject
{
    namespace http
    {
        HTTPParser::HTTPParser(HTTPDocument* document) :
            document{ document },
            status{ ParsingStatus::indeterminate }
        {
        }

        HTTPParser::~HTTPParser()
        {
            
        }

        ParsingStatus HTTPParser::GetStage()
        {
            return this->status;
        }

        shared_ptr<HTTPDocument> HTTPParser::GetDocument()
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
            case expectingHeaderNewLine: this->HandleSynbolForCorrespondence(curentSymbol, '\n', ParsingStage::newLineStart); break;
            case newLineStart: this->HandleNewLineStartSymbol(curentSymbol); break;
            case headerName: this->HandleHeaderNameSymbol(curentSymbol); break;
            case spaceBeforeHaderValue: this->HandleSynbolForCorrespondence(curentSymbol, ' ', ParsingStage::headerValue); break;
            case headerValue: this->HandleHeaderValueSymbol(curentSymbol); break;
            case expectingLineBeforeBody: this->HandleSynbolForCorrespondence(curentSymbol, '\n', ParsingStage::body); break;
            case body: this->HandleBodySymbol(curentSymbol); return;
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

        void HTTPParser::HandleBodySymbol(char curentSymbol)
        {
            this->document->body.push_back(curentSymbol);
        }

        void HTTPParser::HandleSynbolForCorrespondence(char curentSymbol, char requiredSymbol, ParsingStage nextStage)
        {
            if (curentSymbol == requiredSymbol)
            {
                this->stage = nextStage;
            }
            else
            {
                this->status = ParsingStatus::endResultBad;
            }
        }
    }
}
