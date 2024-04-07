#include "HTTPHeaderValueClassField.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		HTTPHeaderValueClassField::HTTPHeaderValueClassField(std::string value) : 
			m_arguments{ value }
		{}

		HTTPHeaderValueClassField::HTTPHeaderValueClassField(std::string name, std::string value) : 
			m_name{ name },
			m_arguments{ value }
		{
		}

		HTTPHeaderValueClassField::HTTPHeaderValueClassField() {}

		HTTPHeaderValueClassField::HTTPHeaderValueClassField(std::string name, HTTPHeaderValueClassFielsArgument argument) : 
			m_name{ name },
			m_arguments{ argument }
		{
		}
	}
}