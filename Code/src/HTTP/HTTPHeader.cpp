#include "HTTPHeader.hpp"

AxxonsoftInternProject::http::HTTPHeader::HTTPHeader() {};

AxxonsoftInternProject::http::HTTPHeader::HTTPHeader(std::string name, std::string value) :
    name{name},
    value{value}
{};
