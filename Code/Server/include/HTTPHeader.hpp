#pragma once

#include <string>

using std::string;

namespace http
{
	class Header
	{
	private:
		string name;
		string value;

	public: 
		Header(string name, string value);

		string ToString();
	};
}