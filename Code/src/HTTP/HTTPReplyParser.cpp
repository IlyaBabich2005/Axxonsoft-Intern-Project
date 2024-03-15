#include "HTTPReplyParser.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		HTTPReplyParser::HTTPReplyParser(std::shared_ptr<HTTPReply> reply) :
			HTTPParser{ std::dynamic_pointer_cast<HTTPDocument>(reply)}
		{
			m_stage = ParsingStage::httpVersion;
		}

		void HTTPReplyParser::handleSymbol(char curentSymbol)
		{
			__super::handleSymbol(curentSymbol);

			switch (m_stage)
			{
			case code: 
				handleCodeSymbol(curentSymbol); 
				break;
			case httpStatus: 
				handleStatusSymbool(curentSymbol);
				break;
			default: break;
			}
		}

		void HTTPReplyParser::handleVersionSymbol(char curentSymbol)
		{
			if (curentSymbol == ' ')
			{
				m_stage = ParsingStage::code;
			}
			else if (curentSymbol != '/' && (!AxxonsoftInternProject::checks::characters::IsChar(curentSymbol) || 
				AxxonsoftInternProject::checks::characters::IsControlChar(curentSymbol) || 
				AxxonsoftInternProject::checks::characters::IsSpesialChar(curentSymbol)))
			{
				m_status = ParsingStatus::endResultBad;
			}
			else
			{
				m_document->m_version.push_back(curentSymbol);
			}
		}

		void HTTPReplyParser::handleStatusSymbool(char curentSymbol)
		{
			if (curentSymbol == '\r')
			{
				m_stage = ParsingStage::expectingHeaderNewLine;
			}
			else if (AxxonsoftInternProject::checks::characters::IsChar(curentSymbol) && 
				!AxxonsoftInternProject::checks::characters::IsDigid(curentSymbol) || curentSymbol != ' ')
			{
				std::dynamic_pointer_cast<HTTPReply>(m_document)->m_status.push_back(curentSymbol);
			}
			else
			{
				m_status = ParsingStatus::endResultBad;
			}
		}

		void HTTPReplyParser::handleCodeSymbol(char curentSymbol)
		{
			if (curentSymbol == ' ')
			{
				m_stage = ParsingStage::httpStatus;
			}
			else if (AxxonsoftInternProject::checks::characters::IsDigid(curentSymbol))
			{
				std::dynamic_pointer_cast<HTTPReply>(m_document)->m_status.push_back(curentSymbol);
			}
			else
			{
				m_status = ParsingStatus::endResultBad;
			}
		}
	}
}