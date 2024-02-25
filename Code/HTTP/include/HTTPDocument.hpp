#pragma once

#include <vector>

#include "HTTPHeader.hpp"
#include "Serializable.hpp"
#include "Stock.hpp"

namespace separators = AxxonsoftInternProject::http::stock::characters::separators;

using separators::httpDocumentLineSeparator,
	  std::begin,
	  std::end,
	  std::vector;

namespace AxxonsoftInternProject
{
	namespace http
	{
		struct HTTPDocument : Serializable
		{
			vector<HTTPHeader> headers;
			string version;
			string body;

		private:
			vector<const_buffer> SerializeHeaders();
			vector<const_buffer> SerializeBody();

		protected:
			vector<const_buffer> SerializeVersion();

		public:
			vector<const_buffer> Serialize() override;
		};
	}
}