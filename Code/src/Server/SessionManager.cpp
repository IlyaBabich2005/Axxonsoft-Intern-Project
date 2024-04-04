#include "SessionManager.hpp"

namespace AxxonsoftInternProject
{
	namespace SERVER
	{
		std::string SessionManager::generateSessionID()
		{
				return AxxonsoftInternProject::http::stock::functions::generateRandomString(Configuration::g_sessionIdSize);
		}

		void SessionManager::AddSession(const std::string& sessionID, const std::string& sessionUsername)
		{
			m_sessions.insert(std::pair<std::string, std::string>(sessionID, sessionUsername));
		}

		Session SessionManager::GetSession(const std::string& username)
		{
			auto session = m_sessions.find(username);

			if (session != m_sessions.end())
			{
				session->second;
			}
			else
			{
				AddSession(generateSessionID(), username);
				return m_sessions[username];
			}
		}

		void SessionManager::Update()
		{
			for (auto it = m_sessions.begin(); it != m_sessions.end();)
			{
				if (std::chrono::duration_cast<std::chrono::minutes>(std::chrono::system_clock::now() - it->second.m_sessionTimeStamp) >= it->second.m_lifetime)
				{
					it = m_sessions.erase(it);
				}
				else
				{
					++it;
				}
			}
		}
	}
}