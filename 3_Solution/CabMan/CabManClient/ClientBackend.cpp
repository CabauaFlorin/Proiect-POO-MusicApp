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
			instance->Connect("2.tcp.ngrok.io", 19494);
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
	olc::net::message<CustomMsgTypes> msg;
	msg.header.id = CustomMsgTypes::ServerPing;

	// Caution with this...
	std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

	msg << timeNow;
	Send(msg);
}

void ClientBackend::MessageConnect()
{
	olc::net::message<CustomMsgTypes> msg;
	msg.header.id = CustomMsgTypes::MessageAll;
	msg << "Clientul s-a autentificat cu succes!\n";
	Send(msg);
}

void ClientBackend::Register(QString mail, QString username, QString parola)
{
	//SQLManager* temp = SQLManager::getInstance();
	SQLManager::getInstance()->insert_data(mail.toStdString(), username.toStdString(), parola.toStdString());
}