#include <iostream>
#include "Server.h"

int main()
{
	setlocale(LC_ALL, "polish");
	std::cout << "Local host: " << sf::IpAddress::LocalHost << std::endl << "LocalAddress: " << sf::IpAddress::getLocalAddress() << std::endl;

	std::cout << "Port: 4422" << std::endl;
	std::cout << "Serwer uruchomiony." << std::endl << std::endl;

	const unsigned short port = 4422;
	Server server(port);
	server.run();
}