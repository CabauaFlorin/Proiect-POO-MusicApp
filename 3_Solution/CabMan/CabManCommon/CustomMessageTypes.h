#pragma once
#include "net_common.h"
namespace olc
{
	namespace net
	{
		enum class CustomMsgTypes : uint32_t
		{
			ServerAccept,
			ServerDeny,
			ServerPing,
			MessageAll,
			ServerMessage,
			LoginRequest,
			ServerLoginResponse,
			RegisterRequest,
			ServerRegisterResponse,
		};
	}
}
