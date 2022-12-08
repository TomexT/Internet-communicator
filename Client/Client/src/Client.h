#pragma once
#include "PacketType.h"
#include "SFML/Network.hpp"

///
/// Klasa obs³uguj¹ca dzia³anie klienta komunikatora. Realizowane jest w niej nawi¹zywanie po³¹czenia z serwerem oraz przesy³ i odbiór pakietów.
///
class Client
{
private:
	///
	/// Przechowuje nazwê klienta.
	///
	std::string name;
	
	///
	/// Przechowuje socket umo¿liwiaj¹cy po³¹czenie siê z klientem.
	///
	sf::TcpSocket user;

public:
	///
	/// Konstruktor wywo³ywany dla klasy Client.
	/// @param name nazwa klienta, dla którego ma zostaæ wywo³any konstruktor.
	///
	Client(const std::string& name);

	///
	/// Destruktor wywo³ywany dla klasy Client.
	///
	~Client();

	///
	/// Metoda ustanawiaj¹ca po³¹czenie z serwerem o danym adresie IP i na danym porcie.
	/// @param IP adres IP urz¹dzenia, na którym uruchomiony jest serwer komunikatora.
	/// @param port okreœla port, na którym ma byæ ustanowione po³¹czenie.
	///
	sf::TcpSocket::Status connect(const sf::IpAddress& IP, unsigned short port);

	///
	/// Metoda wysy³aj¹ca pakiety o konkretnym typie i treœci do serwera.
	/// @param type okreœla rodzaj pakietu, który ma zostaæ przes³any.
	/// @param msg okreœla treœæ przesy³anej wiadomoœci.
	///
	sf::TcpSocket::Status send(PacketType type, const std::string& msg);

	///
	/// Metoda odbieraj¹ca pakiety przychodz¹ce z serwera.
	/// @param msg przyjmuje treœæ otrzymanej wiadomoœci.
	///
	sf::TcpSocket::Status receive(std::string& msg);
};