#include "HTTPHeaderValueClass.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		HTTPHeaderValueClass::HTTPHeaderValueClass(std::string value) : 
			m_fields{ value }
		{
		}

		HTTPHeaderValueClass::HTTPHeaderValueClass() {}
	}
}