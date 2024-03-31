#include "HTTPHeaderValueClass.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		HTTPHeaderValueClass::HTTPHeaderValueClass(std::string value) : 
			m_arguments{ value }
		{
		}

		HTTPHeaderValueClass::HTTPHeaderValueClass() {}
	}
}