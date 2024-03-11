#include "HTTPParser.hpp"

namespace AxxonsoftInternProject
{
    namespace http
    {
        HTTPParser::HTTPParser(std::shared_ptr<HTTPDocument> document) :
            m_document{ document },
            m_status{ ParsingStatus::indeterminate },
            m_contentSize{ 0 },
            m_handledContentSize{ 0 }
        {
        }

        void HTTPParser::handleSymbol(char curentSymbol)
        {
            switch (m_stage)
            {
            case httpVersion: handleVersionSymbol(curentSymbol); break;
            case expectingHeaderNewLine: handleSynbolForCorrespondence(curentSymbol, '\n', ParsingStage::newLineStart); break;
            case newLineStart: handleNewLineStartSymbol(curentSymbol); break;
            case headerName: handleHeaderNameSymbol(curentSymbol); break;
            case spaceBeforeHaderValue: handleSynbolForCorrespondence(curentSymbol, ' ', ParsingStage::headerValue); break;
            case headerValue: handleHeaderValueSymbol(curentSymbol); break;
            case expectingLineBeforeBody: handleSymbolBeforeBody(curentSymbol); break;
            case body: handleBodySymbol(curentSymbol); break;
            }

        }

        void HTTPParser::handleNewLineStartSymbol(char curentSymbol)
        {
            if (curentSymbol == '\r')
            {
                m_stage = ParsingStage::expectingLineBeforeBody;
            }
            else if (!charChecks::IsChar(curentSymbol) || charChecks::IsControlChar(curentSymbol) || charChecks::IsSpesialChar(curentSymbol))
            {
                m_status = ParsingStatus::endResultBad;
            }
            else
            {
                m_document->headers.push_back(HTTPHeader{});
                m_document->headers.back().name.push_back(curentSymbol);
                m_stage = ParsingStage::headerName;
            }
        }

        void HTTPParser::handleHeaderNameSymbol(char curentSymbol)
        {
            if (curentSymbol == ':')
            {
                m_stage = ParsingStage::spaceBeforeHaderValue;
            }
            else if (!charChecks::IsChar(curentSymbol) || charChecks::IsControlChar(curentSymbol) || charChecks::IsSpesialChar(curentSymbol))
            {
                m_status = ParsingStatus::endResultBad;
            }
            else
            {
                m_document->headers.back().name.push_back(curentSymbol);
            }
        }

        void HTTPParser::handleHeaderValueSymbol(char curentSymbol)
        {
            if (curentSymbol == '\r')
            {
                m_stage = ParsingStage::expectingHeaderNewLine;
            }
            else if (!charChecks::IsChar(curentSymbol) || charChecks::IsControlChar(curentSymbol))
            {
                m_status = ParsingStatus::endResultBad;
            }
            else
            {
                m_document->headers.back().value.push_back(curentSymbol);
            }
        }

        void HTTPParser::handleBodySymbol(char curentSymbol)
        {
            m_handledContentSize++;
            m_document->body.push_back(curentSymbol);

            if (m_handledContentSize >= m_contentSize)
            {
                m_status = ParsingStatus::endResultGood;
            }
        }

        void HTTPParser::handleSynbolForCorrespondence(char curentSymbol, char requiredSymbol, ParsingStage nextStage)
        {
            if (curentSymbol == requiredSymbol)
            {
                m_stage = nextStage;
            }
            else
            {
                m_status = ParsingStatus::endResultBad;
            }
        }

        void HTTPParser::handleSymbolBeforeBody(char currentSymbol)
        {
            if (currentSymbol == '\n')
            {
                for (auto header : m_document->headers)
                {
                    if (header.name == headers::names::g_contentLength)
                    {
                        try
                        {
                            m_contentSize = std::stoi(header.value);
                        }
                        catch (std::exception& ex)
                        {
                           std::cout << ex.what() << "\n";
                           m_status = ParsingStatus::endResultBad;
                        }
                        catch (boost::exception& ex)
                        {
                            std::cout << boost::diagnostic_information(ex) << "\n";
                            m_status = ParsingStatus::endResultBad;
                        }
                    }
                }

                if (m_contentSize <= 0)
                {
                    m_status = ParsingStatus::endResultGood;
                }
                else
                {
                    m_stage = ParsingStage::body;
                }
            }
            else
            {
                m_status = ParsingStatus::endResultBad;
            }
        }
    }
}
