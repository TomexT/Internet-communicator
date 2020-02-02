#pragma once
#include "PacketType.h"
#include "SFML/Network.hpp"

///
/// Klasa obs�uguj�ca dzia�anie klienta komunikatora. Realizowane jest w niej nawi�zywanie po��czenia z serwerem oraz przesy� i odbi�r pakiet�w.
///
class Client
{
private:
	///
	/// Przechowuje nazw� klienta.
	///
	std::string name;
	
	///
	/// Przechowuje socket umo�liwiaj�cy po��czenie si� z klientem.
	///
	sf::TcpSocket user;

public:
	///
	/// Konstruktor wywo�ywany dla klasy Client.
	/// @param name nazwa klienta, dla kt�rego ma zosta� wywo�any konstruktor.
	///
	Client(const std::string& name);

	///
	/// Destruktor wywo�ywany dla klasy Client.
	///
	~Client();

	///
	/// Metoda ustanawiaj�ca po��czenie z serwerem o danym adresie IP i na danym porcie.
	/// @param IP adres IP urz�dzenia, na kt�rym uruchomiony jest serwer komunikatora.
	/// @param port okre�la port, na kt�rym ma by� ustanowione po��czenie.
	///
	sf::TcpSocket::Status connect(const sf::IpAddress& IP, unsigned short port);

	///
	/// Metoda wysy�aj�ca pakiety o konkretnym typie i tre�ci do serwera.
	/// @param type okre�la rodzaj pakietu, kt�ry ma zosta� przes�any.
	/// @param msg okre�la tre�� przesy�anej wiadomo�ci.
	///
	sf::TcpSocket::Status send(PacketType type, const std::string& msg);

	///
	/// Metoda odbieraj�ca pakiety przychodz�ce z serwera.
	/// @param msg przyjmuje tre�� otrzymanej wiadomo�ci.
	///
	sf::TcpSocket::Status receive(std::string& msg);
};