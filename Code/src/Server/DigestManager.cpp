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
			for (auto request_pair : m_authRequestPairs)
			{
				if (request_pair.nonce == nonce && request_pair.opaque == opaque)
				{
					return true;
				}
			}

			return false;
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

			if (serverHash == userhash)
			{
				for (auto authPairIterator = m_authRequestPairs.begin(); authPairIterator != m_authRequestPairs.end(); authPairIterator++)
				{
					if(authPairIterator->nonce == nonce)
					{
						m_authRequestPairs.erase(authPairIterator);
						break;
					}
				}

				m_sessions.push_back(generateSessionId());
			}

			return serverHash;
		}

		std::string DigestManager::generateSessionId()
		{
			return AxxonsoftInternProject::http::stock::functions::generateRandomString(Configuration::g_sessionIdSize);
		}

		std::string DigestManager::IsSessionIdValid(const std::string& sessionID)
		{
			for (auto session : m_sessions)
			{
				if (session.m_sessionID == sessionID)
				{
					return session.m_sessionID;
				}
			}
		}

		void DigestManager::AddAuthRequestPair(const std::string& nounce, const std::string& opaque)
		{
			m_authRequestPairs.push_back(AuthPair{ nounce, opaque });
		}
	}
}