#include "HTTPReplyParser.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		HTTPReplyParser::HTTPReplyParser(shared_ptr<HTTPReply> reply) :
			HTTPParser{ dynamic_pointer_cast<HTTPDocument>(reply)}
		{
			this->m_stage = ParsingStage::httpVersion;
		}

		void HTTPReplyParser::handleSymbol(char curentSymbol)
		{
			__super::handleSymbol(curentSymbol);

			switch (m_stage)
			{
			case code: handleCodeSymbol(curentSymbol); break;
			case httpStatus: handleStatusSymbool(curentSymbol); break;
			default: break;
			}
		}

		void HTTPReplyParser::handleVersionSymbol(char curentSymbol)
		{
			if (curentSymbol == ' ')
			{
				m_stage = ParsingStage::code;
			}
			else if (curentSymbol != '/' && (!IsChar(curentSymbol) || IsControlChar(curentSymbol) || IsSpesialChar(curentSymbol)))
			{
				m_status = ParsingStatus::endResultBad;
			}
			else
			{
				m_document->version.push_back(curentSymbol);
			}
		}

		void HTTPReplyParser::handleStatusSymbool(char curentSymbol)
		{
			if (curentSymbol == '\r')
			{
				m_stage = ParsingStage::expectingHeaderNewLine;
			}
			else if (IsChar(curentSymbol) && !IsDigid(curentSymbol) || curentSymbol != ' ')
			{
				dynamic_pointer_cast<HTTPReply>(m_document)->status.push_back(curentSymbol);
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
			else if (IsDigid(curentSymbol))
			{
				dynamic_pointer_cast<HTTPReply>(this->m_document)->status.push_back(curentSymbol);
			}
			else
			{
				m_status = ParsingStatus::endResultBad;
			}
		}
	}
}