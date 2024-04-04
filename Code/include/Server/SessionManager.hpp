#pragma once

#include "Session.hpp"
#include "Configuration.hpp"
#include "Stock.hpp"

#include <map>
#include <string>
#include <strstream>

namespace AxxonsoftInternProject
{
	namespace SERVER
	{
		class SessionManager
		{
		private:
			std::map<std::string, Session> m_sessions;

		private:
			std::string generateSessionID();

		public:
			SessionManager() = default;
			~SessionManager() = default;

			void AddSession(const std::string& sessionID, const std::string& sessionUsername);
			Session GetSession(const std::string& username);
			void Update();
		};
	}
}  