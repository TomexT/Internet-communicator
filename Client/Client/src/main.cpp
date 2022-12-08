#include "Client.h"
#include "PacketType.h"
#include "Window.h"
#include <iostream>

int main()
{
	setlocale(LC_ALL, "polish");
	const unsigned short port = 4422;
	std::cout << "Komunikacja odbywa siê przez port 4422" << std::endl;
	std::cout << "--------------------------------------" << std::endl;
	
	std::string name;
	std::cout << "Podaj nick: ";
	std::getline(std::cin, name);
	Client client(name);

	try
	{
		std::string IP;
		std::cout << "Wybierz IP serwera - wpisz \"LocalHost\", \"LocalAddress\" lub bezpoœrednio adres IP: ";
		std::getline(std::cin, IP);

		sf::TcpSocket::Status status;
		if (IP == "LocalHost")
			status = client.connect(sf::IpAddress::LocalHost, port);
		else if (IP == "LocalAddress")
			status = client.connect(sf::IpAddress::getLocalAddress(), port);
		else
			status = client.connect(IP, port);

		if (status != sf::TcpSocket::Done)
		{
			throw -1;
		}
		client.send(INITIAL_NAME_DATA, name);

	
		sf::RenderWindow window(sf::VideoMode(800, 600), "Okno czatu");
		sf::Font font;

		font.loadFromFile("Fonts/Roboto-Regular.ttf");

		ChatWindow chatBox(sf::Vector2f(50, 100), 700, 5, 20, 15, font);
		chatBox.setFillColor(sf::Color::White);
		chatBox.setOutlineColor(sf::Color::Black);
		chatBox.setCharColor(sf::Color::Black);
		chatBox.connectOnEnter([&](const std::string & s) {client.send(GENERAL_MSG, s); });

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				chatBox.handleEvent(event);
			}
			std::string toBePushed;

			sf::TcpSocket::Status status = client.receive(toBePushed);
			if (status == sf::Socket::Done)
			{
				std::cout << toBePushed << "\n";
				chatBox.push(toBePushed);
			}
			else if (status == sf::Socket::Disconnected)
			{
				chatBox.push("Rozlaczono z serwerem.");
				chatBox.draw(window);
				window.display();
				sf::sleep(sf::seconds(2));
				return -1;
			}

			window.clear(sf::Color::Yellow);
			chatBox.update();
			chatBox.draw(window);
			window.display();
		}
	}
	catch (int errorNumber)
	{
		std::cout << "Po³¹czenie nieudane. Serwer jest wy³¹czony lub podano b³êdne IP. Nr b³êdu: " << errorNumber << std::endl;
		system("pause");
	}
}