#include "HTTPReplyStatus.hpp"

AxxonsoftInternProject::http::ReplyStatus::ReplyStatus(string statusName, string statusCode) : 
    statusName { statusName },
    statusCode { statusCode }
{
}

vector<const_buffer> AxxonsoftInternProject::http::ReplyStatus::Serialize()
{
    vector<const_buffer> serializedStatus;

    serializedStatus.push_back(buffer(this->statusCode));
    serializedStatus.push_back(buffer(whiteSpaceSeparator));
    serializedStatus.push_back(buffer(this->statusName));
    
    return serializedStatus;
}