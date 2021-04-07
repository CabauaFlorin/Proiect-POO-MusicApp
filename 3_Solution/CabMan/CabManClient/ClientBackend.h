#pragma once
#include <olc_net.h>
enum class CustomMsgTypes : uint32_t
{
	ServerAccept,
	ServerDeny,
	ServerPing,
	MessageAll,
	ServerMessage,
};

class ClientBackend : public olc::net::client_interface<CustomMsgTypes> 
{
private:
	static ClientBackend* instance;
	ClientBackend() {}
	~ClientBackend() {}
	ClientBackend(const ClientBackend& src) = delete;
public:
	static ClientBackend& getInstance();
	static void destroyInstance();
	void PingServer();
	void MessageConnect();
};

