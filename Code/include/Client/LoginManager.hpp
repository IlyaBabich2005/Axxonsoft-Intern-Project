#pragma once

#include <string>

namespace AxxonsoftInternProject
{
	namespace Client
	{
		struct LoginManager
		{
			std::string m_nonce;
			std::string m_opaque;
			std::string m_sessonID;
			bool m_isNeedToLogin = false;
			std::string m_realm;
			std::string m_qop;
			std::string m_login;
			std::string m_password;
		};
	}
}