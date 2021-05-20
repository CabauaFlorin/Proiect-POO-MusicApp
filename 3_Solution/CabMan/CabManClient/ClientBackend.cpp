#define _CRT_SECURE_NO_WARNINGS

#include "ClientBackend.h"
ClientBackend* ClientBackend::instance = nullptr;

ClientBackend& ClientBackend::getInstance()
{
	// TODO: insert return statement here
	if (!instance)
	{
		instance = new ClientBackend();
		if (!instance->IsConnected())
		{
			instance->Connect("4.tcp.ngrok.io", 16643);
		}
	}
	return *instance;
}

void ClientBackend::destroyInstance()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void ClientBackend::PingServer()
{
	olc::net::message<olc::net::CustomMsgTypes> msg;
	msg.header.id = olc::net::CustomMsgTypes::ServerPing;

	// Caution with this...
	std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

	msg << timeNow;
	Send(msg);
}

void ClientBackend::MessageConnect()
{
	olc::net::message<olc::net::CustomMsgTypes> msg;
	msg.header.id = olc::net::CustomMsgTypes::MessageAll;
	msg << "Clientul s-a autentificat cu succes!\n";
	Send(msg);
}

void ClientBackend::RegisterRequest(QString mail, QString username, QString parola)
{
	olc::net::message<olc::net::CustomMsgTypes> msg;
	msg.header.id = olc::net::CustomMsgTypes::RegisterRequest;
	char mailToSend[256];
	char usernameToSend[256];
	char passwordToSend[256];
	strcpy(mailToSend, mail.toStdString().c_str());
	strcpy(usernameToSend, username.toStdString().c_str());
	strcpy(passwordToSend, parola.toStdString().c_str());

	msg << mailToSend << usernameToSend << passwordToSend;
	Send(msg);
}

void ClientBackend::LoginRequest(const QString& username, const QString& password)
{
	olc::net::message<olc::net::CustomMsgTypes> msg;
	msg.header.id = olc::net::CustomMsgTypes::LoginRequest;
	char usernameToSend[256];
	char passwordToSend[256];
	strcpy(usernameToSend, username.toStdString().c_str());
	strcpy(passwordToSend, password.toStdString().c_str());

	msg << usernameToSend << passwordToSend;
	Send(msg);
}
