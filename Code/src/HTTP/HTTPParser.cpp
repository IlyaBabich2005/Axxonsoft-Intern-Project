#include "HTTPParser.hpp"

namespace AxxonsoftInternProject
{
    namespace http
    {
        HTTPParser::HTTPParser(shared_ptr<HTTPDocument> document) :
            document{ document },
            status{ ParsingStatus::indeterminate },
            contentSize{ 0 },
            handledContentSize{ 0 }
        {
        }

        shared_ptr<HTTPDocument> HTTPParser::GetParsingResult()
        {
            return this->document;
        }

        void HTTPParser::HandleSymbol(char curentSymbol)
        {
            switch (this->stage)
            {
            case httpVersion: std::cout << "handle version\n";
                this->HandleVersionSymbol(curentSymbol); break;
            case expectingHeaderNewLine: std::cout << "handle NewLine expected\n"; 
                this->HandleSynbolForCorrespondence(curentSymbol, '\n', ParsingStage::newLineStart); break;
            case newLineStart: std::cout << "handle new line start symbol \n"; 
               this->HandleNewLineStartSymbol(curentSymbol); break;
            case headerName: std::cout << "handle header name \n"; 
                this->HandleHeaderNameSymbol(curentSymbol); break;
            case spaceBeforeHaderValue: std::cout << "handle space before header value\n"; 
                this->HandleSynbolForCorrespondence(curentSymbol, ' ', ParsingStage::headerValue); break;
            case headerValue: std::cout << "handle header value\n"; 
                this->HandleHeaderValueSymbol(curentSymbol); break;
            case expectingLineBeforeBody: std::cout << "handle line before body\n"; 
                this->HandleSymbolBeforeBody(curentSymbol); break;
            case body: std::cout << "handle body\n"; 
                this->HandleBodySymbol(curentSymbol); break;
            }

            std::cout << "Status " << this->status << "\n";
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
            else if (!IsChar(curentSymbol) || IsControlChar(curentSymbol))
            {
                this->status = ParsingStatus::endResultBad;
            }
            else
            {
                this->document->headers.back().value.push_back(curentSymbol);
            }
        }

        void HTTPParser::HandleBodySymbol(char curentSymbol)
        {
            if (++this->handledContentSize > this->contentSize)
            {
                this->status = ParsingStatus::endResultGood;
            }
            else
            {
                this->document->body.push_back(curentSymbol);
            }
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

        void HTTPParser::HandleSymbolBeforeBody(char currentSymbol)
        {
            if (currentSymbol == '\n')
            {
                for (auto header : this->document->headers)
                {
                    if (header.name == "Content-Length")
                    {
                        try
                        {
                            this->contentSize = std::stoi(header.value);
                        }
                        catch (...)
                        {
                            this->status = ParsingStatus::endResultBad;
                        }
                    }
                }

                if (this->contentSize <= 0)
                {
                    this->status = ParsingStatus::endResultGood;
                }
                else
                {
                    this->stage = ParsingStage::body;
                }
            }
            else
            {
                this->status = ParsingStatus::endResultBad;
            }
        }
    }
}
