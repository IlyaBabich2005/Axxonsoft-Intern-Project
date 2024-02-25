#pragma once

#include <boost/asio/buffer.hpp>

using std::vector,
	  boost::asio::const_buffer;

namespace AxxonsoftInternProject
{
	namespace http
	{
		class Serializable
		{
			virtual vector<boost::asio::const_buffer> Serialize() = 0;
		};
	}
}