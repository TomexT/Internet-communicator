#include <iostream>
#include "Server.h"
#include "PacketType.h"
#include <windows.h>

Server::Server(unsigned short port)
{
	listener.listen(port);
	listener.setBlocking(false);
}

Server::~Server() {}

void Server::broadCast(PacketType type, const std::string & msg)
{
	for (Clients::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		sf::Packet packet;
		packet << type << msg;
		it->first->send(packet);
	}
}

void Server::handlePackets()
{
	for (Clients::iterator it = clients.begin(); it != clients.end();)
	{
		sf::Packet packet;
		sf::TcpSocket::Status status = it->first->receive(packet);

		switch (status)
		{
		case sf::TcpSocket::Done:
			PacketType type;
			packet >> type;
			if (type == INITIAL_NAME_DATA)
			{
				packet >> it->second;
				std::cout << it->second << " dolaczyl" << std::endl;
				broadCast(INITIAL_NAME_DATA, it->second + " dolaczyl\n");
			}
			else if (type == GENERAL_MSG)
			{
				std::string msg;
				packet >> msg;
				std::cout << it->second << ": " << msg << std::endl;
				broadCast(GENERAL_MSG, it->second + ": " + msg);
			}
			++it;
			break;

		case sf::TcpSocket::Disconnected:
			std::cout << it->second << " rozlaczyl sie" << std::endl;
			broadCast(GENERAL_MSG, it->second + " rozlaczyl sie\n");
			it = clients.erase(it);
			break;

		default:
			++it;
		}
	}
}

void Server::run()
{
	sf::Thread thread([&]()
	{
		std::string s;
		while (1)
		{
			std::getline(std::cin, s);
			broadCast(SERVER_MSG, "SERVER: " + s);
		}
	});
	thread.launch();

	sf::TcpSocket * nextClient = nullptr;
	while (1)
	{
		if (nextClient == nullptr)
		{
			nextClient = new sf::TcpSocket;
			nextClient->setBlocking(false);
		}
		if (listener.accept(*nextClient) == sf::TcpSocket::Done)
		{
			clients.insert(std::make_pair(nextClient, ""));
			nextClient = nullptr;
		}
		handlePackets();
	}
}