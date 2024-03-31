#include "Session.hpp"

namespace AxxonsoftInternProject
{
	namespace SERVER
	{
		Session::Session(const std::string& sessionID) : 
			m_sessionID(sessionID),
			m_lifetime(Configuration::g_sessionLifetimeInMinutes),
			m_sessionTimeStamp(std::chrono::system_clock::now())
		{
		}
	}
}