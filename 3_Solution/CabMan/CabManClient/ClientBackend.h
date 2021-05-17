#pragma once
#include <olc_net.h>
#include <qstring.h>


class ClientBackend : public olc::net::client_interface<olc::net::CustomMsgTypes> 
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
	void RegisterRequest(QString mail, QString username, QString parola);
	void LoginRequest(const QString& username, const QString& password);
};