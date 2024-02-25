#pragma once

#include "Serializable.hpp"
#include "Stock.hpp"

namespace separators = AxxonsoftInternProject::http::stock::characters::separators;

using boost::asio::buffer,
	  separators::whiteSpaceSeparator,
	  std::string;

namespace AxxonsoftInternProject
{
	namespace http
	{
		class ReplyStatus : Serializable
		{
		private: 
			string statusName;
			string statusCode;

		public: 
			ReplyStatus(string statusName, string statusCode);

			vector<const_buffer> Serialize() override;
		};
	}
}