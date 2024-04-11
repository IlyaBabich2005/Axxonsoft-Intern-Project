#include "DigestManager.hpp"

namespace AxxonsoftInternProject
{
	namespace SERVER
	{
		DigestManager::DigestManager()
		{
			AddUser(Configuration::g_adminUsername, Configuration::g_adminPassword);
		}

		void DigestManager::Update()
		{
			for (auto session_iterator = m_sessions.begin(); session_iterator != m_sessions.end();)
			{
				if (std::chrono::duration_cast<std::chrono::minutes>(std::chrono::system_clock::now() - session_iterator->m_sessionTimeStamp) >= session_iterator->m_lifetime)
				{
					session_iterator = m_sessions.erase(session_iterator);
				}
				else
				{
					++session_iterator;
				}
			}
		}

		void DigestManager::AddUser(const std::string& username, const std::string& password)
		{
			m_usersData.insert(std::pair<std::string, std::string>(username, password));
		}

		bool DigestManager::IsAuthPairValid(std::string nonce, std::string opaque)
		{
			return m_authRequestPairs.find(nonce) != m_authRequestPairs.end() && 
				m_authRequestPairs[nonce] == opaque ? true : false;
		}

		std::string DigestManager::getServerHash(const std::string authString)
		{
				boost::uuids::detail::md5 hash;
				boost::uuids::detail::md5::digest_type digest;
				std::string serverHash;

				hash.process_bytes(authString.data(), authString.size());
				hash.get_digest(digest);

				const auto intDigest = reinterpret_cast<const int*>(digest);
				boost::algorithm::hex(intDigest, intDigest + (sizeof(boost::uuids::detail::md5::digest_type)/sizeof(int)), std::back_inserter(serverHash));

				return serverHash;
		}

		std::string DigestManager::GetSessionId(const std::string& userhash, const std::string& username, const std::string& nonce)
		{
			std::string serverHash;

			if (m_usersData.find(username) != m_usersData.end())
			{
				serverHash = getServerHash(username + nonce + m_usersData[username]);
			}

			std::string sessionID = generateSessionId();

			if (serverHash == userhash)
			{
				m_authRequestPairs.erase(nonce);

				m_sessions.push_back(sessionID);
			}

			return sessionID;
		}

		std::string DigestManager::generateSessionId()
		{
			return AxxonsoftInternProject::http::stock::functions::generateRandomString(Configuration::g_sessionIdSize);
		}

		bool DigestManager::IsSessionIdValid(const std::string& sessionID)
		{
			for (auto session : m_sessions)
			{
				if (session.m_sessionID == sessionID)
				{
					return true;
				}
			}

			return false;
		}

		void DigestManager::AddAuthRequestPair(const std::string& nounce, const std::string& opaque)
		{
			m_authRequestPairs.insert(std::pair<std::string, std::string>{ nounce, opaque });
		}
	}
}