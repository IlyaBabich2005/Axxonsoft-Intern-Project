#include "HTTPHeaderValueClassFieldArgument.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		HTTPHeaderValueClassFielsArgument::HTTPHeaderValueClassFielsArgument(const std::string& value) :
			m_value{ value }
		{
		}

		HTTPHeaderValueClassFielsArgument::HTTPHeaderValueClassFielsArgument(const std::string& value, const bool& isString) :
			m_value{ value },
			m_isString{ isString }
		{
		}

		HTTPHeaderValueClassFielsArgument::HTTPHeaderValueClassFielsArgument()
		{
		}
	}
}