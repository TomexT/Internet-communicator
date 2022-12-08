#include "Client.h"
#include <iostream>

Client::Client(const std::string & name) : name(name) {}

Client::~Client() {}

sf::TcpSocket::Status Client::connect(const sf::IpAddress & IP, unsigned short port)
{
	sf::TcpSocket::Status status = user.connect(IP, port);
	user.setBlocking(false);
	return status;
}

sf::TcpSocket::Status Client::send(PacketType type, const std::string & msg)
{
	sf::Packet packet;
	packet << type << msg;
	return user.send(packet);
}

sf::TcpSocket::Status Client::receive(std::string & msg)
{
	sf::Packet packet;
	sf::TcpSocket::Status status = user.receive(packet);
	PacketType type;
	packet >> type;
	if (status == sf::Socket::Done)
	{
		std::cout << msg << "\n";
		packet >> msg;
	}
	return status;
}