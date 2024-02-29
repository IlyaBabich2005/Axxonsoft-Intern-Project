#pragma once

#include <string>
#include "Serializable.hpp"
#include "Stock.hpp"

namespace stock = AxxonsoftInternProject::http::stock;

using stock::characters::separators::headerNameValueSeparator,
	boost::asio::buffer,
	  std::string;

namespace AxxonsoftInternProject
{
	namespace http
	{
		struct HTTPHeader : public Serializable
		{
			string name;
			string value;

			HTTPHeader();
			HTTPHeader(string name, string value);

			vector<const_buffer> Serialize() override;
		};
	}
}