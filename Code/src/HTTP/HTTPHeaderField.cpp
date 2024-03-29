#include "HTTPHeaderField.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		HTTPHeaderField::HTTPHeaderField(std::string value)
		{
			m_value = value;
		}

		HTTPHeaderField::HTTPHeaderField() {}
	}
}