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
			m_sessionManager.Update();
		}

		void DigestManager::AddUser(const std::string& username, const std::string& password)
		{
			m_usersData.insert(std::pair<std::string, std::string>(username, password));
		}

		bool DigestManager::IsOpaqueValid(const std::string& nonce, const std::string& opaque)
		{
			return m_authRequestPairs.find(nonce) != m_authRequestPairs.end() && m_authRequestPairs[nonce] == opaque;
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

		std::string DigestManager::GetSessionId(const std::string& userhash, const std::string& username, const std::string& nounce)
		{
			std::string serverHash;

			if (m_usersData.find(username) != m_usersData.end())
			{
				serverHash = getServerHash(username + nounce + m_usersData[username]);
			}

			if (serverHash == userhash)
			{
				m_authRequestPairs.erase(serverHash);
				m_sessionManager.AddSession(serverHash, username);
			}

			return serverHash;
		}

		std::string DigestManager::GetSessionId(const std::string& sessionID)
		{
			return m_sessionManager.GetSession(sessionID).m_sessionID;
		}

		void DigestManager::AddAuthRequestPair(const std::string& nounce, const std::string& opaque)
		{
			m_authRequestPairs.insert(std::pair<std::string, std::string>(nounce, opaque));
		}
	}
}