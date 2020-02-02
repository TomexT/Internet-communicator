#pragma once
#include <deque>
#include <functional>
#include "SFML/Graphics.hpp"

namespace sf
{
	class Packet;
}

///
/// Klasa umo�liwiaj�ca utworzenie okna do obs�ugi czatu przy u�yciu biblioteki SFML. Okno to ma okre�lone wymiary i parametry.
///
class ChatWindow
{
private:
	///
	/// Okre�la wielko�� zapisywanej historii rozmowy.
	///
	const std::size_t historyLength;

	///
	/// Okre�la grubo�� obramowa�.
	///
	const float thickness;

	///
	/// Okre�la wielko�� wypisywanych znak�w.
	///
	const int charSize;

	///
	/// Okre�la d�ugo��, zmienn� x, dla matematycznego wektora.
	///
	const float length;

	///
	/// Okre�la kszta�t okna wy�wietlaj�cego histori� konwersacji i jego parametry.
	///
	sf::RectangleShape historyBox;
	
	///
	/// Okre�la kszta�t okna wy�wietlaj�cego bufor konwersacji i jego parametry.
	///
	sf::RectangleShape bufferBox;

	///
	/// Umo�liwia zapisywanie i rysowanie tekstu w oknie buforu konwersacji.
	///
	sf::Text text;

	///
	/// Umo�liwia zapisywanie i rysowanie tekstu w oknie historii konwersacji.
	///
	sf::Text historyText;

	///
	/// Kolejka dwukierunkowa przechowuj�ca zmienne typu string; zapsuje ona histori� ca�ej konwersacji.
	///
	std::deque<std::string> history;
	
	///
	/// Przechowuje tekst wpisany przez klienta w oknie bufora konwersacji.
	///
	std::string buffer;

	///
	/// Funkcja polimorficzna okre�laj�ca wykonanie konkretnego dzia�ania z u�yciem zmiennej typu string przekazanej do tej funcji, gdy zostanie wci�ni�ty klawisz Enter.
	///
	std::function<void(const std::string & s)> onEnter;

public:
	///
	/// Konstruktor wywo�ywany dla klasy ChatWindow.
	/// @param pos przechowuje wsp�rz�dne x i y matematycznego wektora.
	/// @param length okre�la d�ugo��, zmienn� x, dla matematycznego wektora.
	/// @param thickness okre�la grubo�� obramowa�.
	/// @param charSize okre�la wielko�� wpisywanych znak�w.
	/// @param historyLength okre�la wielko�� zapisywanej historii rozmowy.
	/// @param font okre�la czcionk� dla wy�witlanych znak�w.
	///
	ChatWindow(const sf::Vector2f pos, const float length, const float thickness, const int charSize, 
		const std::size_t historyLength, const sf::Font & font);

	///
	/// Destruktor wywo�ywany dla klasy ChatWindow.
	///
	~ChatWindow();

	///
	/// Metoda ustawiaj�ca d�ugo�� i tre�� tekstu do wy�wietlenia w oknie czatu na podstawie tekstu wpisanego w bufor. 
	///
	void update();

	/** Metoda wykonuj�ca konkretne dzia�ania w zale�no�ci od pojawiaj�cych si� w buforze znak�w. 
	  * Je�li u�ytkownik wprowadzi znak "Enter", wpisania w buforze wiadomo�� zostanie wys�ana.
	  * Je�li u�ytkownik wprowadzi znak "Backspace", z bufora zosatnie usuni�ty ostatni znak.
	*/
	void handleEvent(sf::Event & event);

	///
	/// Metoda dodaj�ca napisan� wiadomo�� na pocz�tek kolejki i usuwaj�ca najstarsz� wiadomo�� z kolejki, je�li wielko�� historii zostanie przekroczona.
	///
	void push(const std::string & s);
	
	///
	/// Metoda wykorzystuj�ca funkcj� polimorficzn�, kt�ra realizuje po��czenie oraz wys�anie wiadomo�ci wst�pnej, gdy zostanie wci�ni�ty klawisz Enter.
	///
	void connectOnEnter(std::function<void(const std::string & s)> func);

	///
	/// Metoda rysuj�ca okno czatu o parametrach przekazanych w zmiennej window.
	///
	void draw(sf::RenderWindow & window);

	///
	/// Metoda ustawiaj�ca kolor obramowa� okna.
	///
	void setOutlineColor(const sf::Color & color);
	
	///
	/// Metoda ustawiaj�ca kolor wype�nienia okna.
	///
	void setFillColor(const sf::Color & color);

	///
	/// Metoda ustawiaj�ca kolor znak�w.
	///
	void setCharColor(const sf::Color & color);
};