#pragma once 

#include "Configuration.hpp"

#include <string>
#include <chrono>

namespace AxxonsoftInternProject
{
	namespace SERVER
	{
		struct Session
		{
			std::string m_sessionID;
			std::chrono::minutes m_lifetime;
			std::chrono::time_point<std::chrono::system_clock> m_sessionTimeStamp;

			Session(const std::string& sessionID);
			Session();
		};
	}
}