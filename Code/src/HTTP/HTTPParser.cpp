#include "HTTPParser.hpp"

namespace AxxonsoftInternProject
{
    namespace http
    {
        HTTPParser::HTTPParser(std::shared_ptr<HTTPDocument> document) :
            m_document{ document },
            m_status{ ParsingStatus::indeterminate },
            m_contentSize{ 0 },
            m_handledContentSize{ 0 },
            m_isHeaderClassDefined {false},
            m_isStringValueReading{false},
            m_isHeaserFieldNameDefined{false},
            m_isArgumentString{false}
        {
        }

        void HTTPParser::handleSymbol(char curentSymbol)
        {
            switch (m_stage)
            {
            case httpVersion: 
                handleVersionSymbol(curentSymbol); 
                break;
            case expectingHeaderNewLine: 
                handleSynbolForCorrespondence(curentSymbol, '\n', ParsingStage::newLineStart); 
                break;
            case newLineStart: 
                handleNewLineStartSymbol(curentSymbol); 
                break;
            case headerName: 
                handleHeaderNameSymbol(curentSymbol); 
                break;
            case spaceBeforeHaderValue: 
                handleSynbolForCorrespondence(curentSymbol, ' ', ParsingStage::headerValue); 
                break;
            case headerValue: 
                handleHeaderValueSymbol(curentSymbol); 
                break;
            case expectingLineBeforeBody: 
                handleSymbolBeforeBody(curentSymbol); 
                break;
            case body: 
                handleBodySymbol(curentSymbol); 
                break;
            }

        }

        void HTTPParser::handleNewLineStartSymbol(char curentSymbol)
        {
            if (curentSymbol == '\r')
            {
                m_stage = ParsingStage::expectingLineBeforeBody;
            }
            else if (!AxxonsoftInternProject::checks::characters::IsChar(curentSymbol) || 
                AxxonsoftInternProject::checks::characters::IsControlChar(curentSymbol) || 
                AxxonsoftInternProject::checks::characters::IsSpesialChar(curentSymbol))
            {
                m_status = ParsingStatus::endResultBad;
            }
            else
            {
                m_document->m_headers.push_back(HTTPHeader{});
                m_document->m_headers.back().m_name.push_back(curentSymbol);
                m_stage = ParsingStage::headerName;
            }
        }

        void HTTPParser::handleHeaderNameSymbol(char curentSymbol)
        {
            if (curentSymbol == ':')
            {
                m_stage = ParsingStage::spaceBeforeHaderValue;
            }
            else if (!AxxonsoftInternProject::checks::characters::IsChar(curentSymbol) || 
                AxxonsoftInternProject::checks::characters::IsControlChar(curentSymbol) || 
                AxxonsoftInternProject::checks::characters::IsSpesialChar(curentSymbol))
            {
                m_status = ParsingStatus::endResultBad;
            }
            else
            {
                m_document->m_headers.back().m_name.push_back(curentSymbol);
            }
        }

        void HTTPParser::handleHeaderValueSymbol(char curentSymbol)
        {
            if (AxxonsoftInternProject::checks::characters::IsChar(curentSymbol) &&
                !AxxonsoftInternProject::checks::characters::IsControlChar(curentSymbol))
            {
                if (!m_isStringValueReading && curentSymbol != '"')
                {
                    handleNonStringHeaderValueSymbol(curentSymbol);
                }
                else if (curentSymbol == '"')
                {
                    m_isStringValueReading = !m_isStringValueReading;
                    m_isArgumentString = true;
                }  
                else
                {
                    m_tempHeaderString.push_back(curentSymbol);
                }
            }
            else
            {
                if (curentSymbol == '\r')
                {
                    handleRSymbolInHeaderValue(curentSymbol);
                }
                else if(curentSymbol == '\0')
				{
                    return;
				}
                else
                {
                    m_status = ParsingStatus::endResultBad;
                }
            }
        }

        void HTTPParser::handleBodySymbol(char curentSymbol)
        {
            m_handledContentSize++;

            m_document->m_body.push_back(curentSymbol);

            if (m_handledContentSize >= m_contentSize)
            {
                m_status = ParsingStatus::endResultGood;
                return;
            }
        }

        void HTTPParser::handleWhiteSpaceSymbolInHeaderValue(char curentSymbol)
        {
            m_isHeaderClassDefined = true;
            m_document->m_headers.back().m_classes.push_back(HTTPHeaderValueClass{});
            m_document->m_headers.back().m_classes.back().m_name = m_tempHeaderString;
        }

        void HTTPParser::handleEqualsSymbolInHeaderValue(char curentSymbol)
        {
            m_isHeaserFieldNameDefined = true;

            defineHeaderClass();

            m_document->m_headers.back().m_classes.back().m_fields.push_back(HTTPHeaderValueClassField{});
            m_document->m_headers.back().m_classes.back().m_fields.back().m_name = m_tempHeaderString;
        }

        void HTTPParser::handleCommaSymbolInHeaderValue(char curentSymbol)
        {
            defineHeaderFieldName();

            m_document->m_headers.back().m_classes.back().m_fields.back().m_arguments.push_back(HTTPHeaderValueClassFielsArgument{ m_tempHeaderString, m_isArgumentString });
            m_isHeaserFieldNameDefined = false;
            m_isArgumentString = false;
            m_stage = ParsingStage::spaceBeforeHaderValue;
        }

        void HTTPParser::handleSemicolonSymbolInHeaderValue(char curentSymbol)
        {
            defineHeaderFieldName();

            m_document->m_headers.back().m_classes.back().m_fields.back().m_arguments.push_back(HTTPHeaderValueClassFielsArgument{ m_tempHeaderString, m_isArgumentString });
            m_isHeaserFieldNameDefined = false;
            m_isHeaderClassDefined = false;
            m_isArgumentString = false;
            m_stage = ParsingStage::spaceBeforeHaderValue;
        }

        void HTTPParser::handleRSymbolInHeaderValue(char curentSymbol)
        {
            defineHeaderFieldName();

			m_document->m_headers.back().m_classes.back().m_fields.back().m_arguments.push_back(HTTPHeaderValueClassFielsArgument{ m_tempHeaderString, m_isArgumentString });

            m_isStringValueReading = false;
            m_isHeaderClassDefined = false;
            m_isHeaserFieldNameDefined = false;
            m_isArgumentString = false;
            m_tempHeaderString.clear();
            m_stage = ParsingStage::expectingHeaderNewLine;
        }

        void HTTPParser::handleNonStringHeaderValueSymbol(char curentSymbol)
        {
            switch (curentSymbol)
            {
            case ' ':
                handleWhiteSpaceSymbolInHeaderValue(curentSymbol);
                break;
            case '=':
                handleEqualsSymbolInHeaderValue(curentSymbol);
                break;
            case ';':
                handleSemicolonSymbolInHeaderValue(curentSymbol);
                break;
            case ',':
                handleCommaSymbolInHeaderValue(curentSymbol);
                break;
			default:
                m_tempHeaderString.push_back(curentSymbol);
                return;
            }

            m_tempHeaderString.clear();
        }

        void HTTPParser::defineHeaderClass()
        {
            if (!m_isHeaderClassDefined)
            {
                m_document->m_headers.back().m_classes.push_back(HTTPHeaderValueClass{});
                m_isHeaderClassDefined = true;
            }
        }

        void HTTPParser::defineHeaderFieldName()
        {
            if (!m_isHeaserFieldNameDefined)
            {
                defineHeaderClass();

                m_document->m_headers.back().m_classes.back().m_fields.push_back(HTTPHeaderValueClassField{});
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
                for (auto header : m_document->m_headers)
                {
                    if (header.m_name == AxxonsoftInternProject::http::stock::headers::names::g_contentLength)
                    {
                        try
                        {
                            m_contentSize = std::stoi(header.m_classes.back().m_fields.back().m_arguments.back().m_value);
                        }
                        catch (std::exception& ex)
                        {
                           std::cout << boost::format("%1%\n") % ex.what();
                           m_status = ParsingStatus::endResultBad;
                        }
                        catch (boost::exception& ex)
                        {
                            std::cout << boost::format("%1%\n") % boost::diagnostic_information(ex);
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
