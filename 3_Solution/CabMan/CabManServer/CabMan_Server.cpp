#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <olc_net.h>

class Server_app : public olc::net::server_interface<olc::net::CustomMsgTypes>
{
public:
	Server_app(uint16_t nPort) : olc::net::server_interface<olc::net::CustomMsgTypes>(nPort)
	{

	}

protected:
	virtual bool OnClientConnect(std::shared_ptr<olc::net::connection<olc::net::CustomMsgTypes>> client)
	{
		olc::net::message<olc::net::CustomMsgTypes> msg;
		msg.header.id = olc::net::CustomMsgTypes::ServerAccept;
		client->Send(msg);
		return true;
	}

	// Called when a client appears to have disconnected
	virtual void OnClientDisconnect(std::shared_ptr<olc::net::connection<olc::net::CustomMsgTypes>> client)
	{
		std::cout << "Removing client [" << client->GetID() << "]\n";
	}

	// Called when a message arrives
	virtual void OnMessage(std::shared_ptr<olc::net::connection<olc::net::CustomMsgTypes>> client, olc::net::message<olc::net::CustomMsgTypes>& msg)
	{
		switch (msg.header.id)
		{
		case olc::net::CustomMsgTypes::ServerPing:
		{
			std::cout << "[" << client->GetID() << "]: Server Ping\n";

			// Simply bounce message back to client
			client->Send(msg);
		}
		break;

		case olc::net::CustomMsgTypes::MessageAll:
		{
			std::cout << "[" << client->GetID() << "]: Message All\n";

			// Construct a new message and send it to all clients
			olc::net::message<olc::net::CustomMsgTypes> msg;
			msg.header.id = olc::net::CustomMsgTypes::ServerMessage;
			msg << client->GetID();
			//std::cout << msg;
			MessageAllClients(msg, client);
		}
		break;
		
		case olc::net::CustomMsgTypes::ServerMessage:
		{
			std::cout << "[" << client->GetID() << "]: Server Message\n";
		}
		break;


		case olc::net::CustomMsgTypes::LoginRequest:
		{
			std::cout << "[" << client->GetID() << "]: User Login Request\n";
			char username[256];
			char password[256];

			msg >> password >> username;
			char responseFromLogin[100];
			if (OnLoginRequest(username, password))
			{
				strcpy(responseFromLogin, "SuccessLogin");
			}
			else
			{
				strcpy(responseFromLogin, "FailLogin");
			}

			msg.header.id = olc::net::CustomMsgTypes::ServerLoginResponse;
			msg << responseFromLogin;
			client->Send(msg);
		}
		break;

		case olc::net::CustomMsgTypes::RegisterRequest:
		{
			std::cout << "[" << client->GetID() << "]: User Register Request\n";
			char mail[256];
			char username[256];
			char password[256];

			msg >> password >> username >> mail;
			char ResponseFromRegister[100];
			int register_code = OnRegisterRequest(mail, username, password);
			if (register_code == -1)
			{
				strcpy(ResponseFromRegister, "UserAlready");
			}
			if (register_code == 0)
			{
				strcpy(ResponseFromRegister, "SuccessRegister");
			}

			msg.header.id = olc::net::CustomMsgTypes::ServerRegisterResponse;
			msg << ResponseFromRegister;
			client->Send(msg);
		}
		break;
		}
	}
};

int main()
{
	Server_app server(60000);
	server.Start();

	while (1)
	{
		server.Update(-1, true);
	}



	return 0;
}