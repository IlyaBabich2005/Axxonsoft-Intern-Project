#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>

#include <map>

#include "Session.hpp"
#include "Config.hpp"
#include "Stock.hpp"

#define BOOST_UUID_COMPAT_PRE_1_71_MD5

namespace AxxonsoftInternProject
{
	namespace SERVER
	{
		class DigestManager
		{
		private:
			std::map<std::string, std::string> m_usersData;
			std::map<std::string, std::string> m_authRequestPairs;
			std::vector<Session> m_sessions;

		private:
			std::string getServerHash(const std::string authString);
			std::string generateSessionId();

		public:
			DigestManager();
			void Update();
			void AddUser(const std::string& username, const std::string& password);
			void AddAuthRequestPair(const std::string& nounce, const std::string& opaque);
			bool IsAuthPairValid(std::string nonce, std::string opaque);
			std::string GetSessionId(const std::string& userhash, const std::string& username, const std::string& nounce);
			bool IsSessionIdValid(const std::string& sessionID);
		};
	}
}