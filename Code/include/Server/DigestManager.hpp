#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>

#include "SessionManager.hpp"
#include "Config.hpp"

#define BOOST_UUID_COMPAT_PRE_1_71_MD5

namespace AxxonsoftInternProject
{
	namespace SERVER
	{
		class DigestManager
		{
		private:
			std::map<std::string, std::string> m_authRequestPairs;
			std::map<std::string, std::string> m_usersData;
			SessionManager m_sessionManager;

		private:
			std::string getServerHash(const std::string authString);

		public:
			DigestManager();
			void Update();
			void AddUser(const std::string& username, const std::string& password);
			void AddAuthRequestPair(const std::string& nounce, const std::string& opaque);
			bool IsOpaqueValid(const std::string& nonce, const std::string& opaque);
			std::string GetSessionId(const std::string& userhash, const std::string& username, const std::string& nounce);
			std::string GetSessionId(const std::string& username);
		};
	}
}