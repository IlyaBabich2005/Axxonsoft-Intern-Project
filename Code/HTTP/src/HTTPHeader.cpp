#include "HTTPHeader.hpp"

vector<const_buffer> AxxonsoftInternProject::http::HTTPHeader::Serialize()
{
    vector<const_buffer> serializedHeader;

    serializedHeader.push_back(buffer(this->name));
    serializedHeader.push_back(buffer(headerNameValueSeparator));
    serializedHeader.push_back(buffer(this->value));

    return serializedHeader;
}
