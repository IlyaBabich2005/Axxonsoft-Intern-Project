#include "HTTPHeader.hpp"

AxxonsoftInternProject::http::HTTPHeader::HTTPHeader() {};

AxxonsoftInternProject::http::HTTPHeader::HTTPHeader(std::string name, std::string value) :
    m_name{name},
    m_value{value}
{};
