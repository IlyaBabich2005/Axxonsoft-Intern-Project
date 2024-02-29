#include "HTTPHeader.hpp"

AxxonsoftInternProject::http::HTTPHeader::HTTPHeader() {};

AxxonsoftInternProject::http::HTTPHeader::HTTPHeader(string name, string value) :
    name{name},
    value{value}
{};
