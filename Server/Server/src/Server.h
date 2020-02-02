#pragma once
#include "SFML/Network.hpp"
#include "PacketType.h"
#include <map>

///
/// Klasa obs�uguj�ca dzia�anie serwera. Realizowane jest w niej ��czenie si� z klientami oraz przesy�, odbi�r i odpowiedni podzia� pakiet�w na typy.
///
class Server
{
private:
	///
	/// Tworzy nowy typ, b�d�cy map� zawieraj�c� pary klucz-warto��; przechowuje TcpSocket dla klienta o danej nazwie.
	///
	typedef std::map<sf::TcpSocket*, std::string> Clients;

	///
	/// Umo�liwia zapis danych potrzebnych serwerowi do obs�ugi kolejnych klient�w.
	///
	Clients clients;

	///
	/// Umo�liwia ustawienie cia�a nas�uchuj�cego przyp�yw pakiet�w na danym porcie.
	///
	sf::TcpListener listener;

	///
	/// Metoda zajmuj�ca si� pakietami przychodz�cymi i wychodz�cymi.
	///
	void handlePackets();

	///
	/// Metoda przesy�aj�ca wszystkie wiadomo�ci z okre�leniem, kto jest nadawc� danej wiadomo�ci.
	/// @param type okre�la rodzaj pakietu, kt�ry ma zosta� przes�any.
	/// @param msg okre�la tre�� przesy�anej wiadomo�ci.
	///
	void broadCast(PacketType type, const std::string& msg);

public:
	///
	/// Konstruktor wywo�ywany dla klasy Server.
	/// @param port okre�la port, dla kt�rego ma zosta� wywo�any konstruktor.
	///
	Server(unsigned short port);
	
	///
	/// Destruktor wywo�ywany dla klasy Server.
	///
	~Server();

	///
	/// Metoda okre�laj�ca dzia�anie serwera.
	///
	void run();
};