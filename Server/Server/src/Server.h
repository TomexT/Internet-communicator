#pragma once
#include "SFML/Network.hpp"
#include "PacketType.h"
#include <map>

///
/// Klasa obs³uguj¹ca dzia³anie serwera. Realizowane jest w niej ³¹czenie siê z klientami oraz przesy³, odbiór i odpowiedni podzia³ pakietów na typy.
///
class Server
{
private:
	///
	/// Tworzy nowy typ, bêd¹cy map¹ zawieraj¹c¹ pary klucz-wartoœæ; przechowuje TcpSocket dla klienta o danej nazwie.
	///
	typedef std::map<sf::TcpSocket*, std::string> Clients;

	///
	/// Umo¿liwia zapis danych potrzebnych serwerowi do obs³ugi kolejnych klientów.
	///
	Clients clients;

	///
	/// Umo¿liwia ustawienie cia³a nas³uchuj¹cego przyp³yw pakietów na danym porcie.
	///
	sf::TcpListener listener;

	///
	/// Metoda zajmuj¹ca siê pakietami przychodz¹cymi i wychodz¹cymi.
	///
	void handlePackets();

	///
	/// Metoda przesy³aj¹ca wszystkie wiadomoœci z okreœleniem, kto jest nadawc¹ danej wiadomoœci.
	/// @param type okreœla rodzaj pakietu, który ma zostaæ przes³any.
	/// @param msg okreœla treœæ przesy³anej wiadomoœci.
	///
	void broadCast(PacketType type, const std::string& msg);

public:
	///
	/// Konstruktor wywo³ywany dla klasy Server.
	/// @param port okreœla port, dla którego ma zostaæ wywo³any konstruktor.
	///
	Server(unsigned short port);
	
	///
	/// Destruktor wywo³ywany dla klasy Server.
	///
	~Server();

	///
	/// Metoda okreœlaj¹ca dzia³anie serwera.
	///
	void run();
};