#include "HTTPHeader.hpp"

AxxonsoftInternProject::http::HTTPHeader::HTTPHeader()
{}

AxxonsoftInternProject::http::HTTPHeader::HTTPHeader(std::string name) : 
	m_name{name}
{
};

AxxonsoftInternProject::http::HTTPHeader::HTTPHeader(std::string name, std::string value) :
    m_name{name},
    m_classes{value}
{};
