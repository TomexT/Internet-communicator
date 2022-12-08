#pragma once
#include <deque>
#include <functional>
#include "SFML/Graphics.hpp"

namespace sf
{
	class Packet;
}

///
/// Klasa umo¿liwiaj¹ca utworzenie okna do obs³ugi czatu przy u¿yciu biblioteki SFML. Okno to ma okreœlone wymiary i parametry.
///
class ChatWindow
{
private:
	///
	/// Okreœla wielkoœæ zapisywanej historii rozmowy.
	///
	const std::size_t historyLength;

	///
	/// Okreœla gruboœæ obramowañ.
	///
	const float thickness;

	///
	/// Okreœla wielkoœæ wypisywanych znaków.
	///
	const int charSize;

	///
	/// Okreœla d³ugoœæ, zmienn¹ x, dla matematycznego wektora.
	///
	const float length;

	///
	/// Okreœla kszta³t okna wyœwietlaj¹cego historiê konwersacji i jego parametry.
	///
	sf::RectangleShape historyBox;
	
	///
	/// Okreœla kszta³t okna wyœwietlaj¹cego bufor konwersacji i jego parametry.
	///
	sf::RectangleShape bufferBox;

	///
	/// Umo¿liwia zapisywanie i rysowanie tekstu w oknie buforu konwersacji.
	///
	sf::Text text;

	///
	/// Umo¿liwia zapisywanie i rysowanie tekstu w oknie historii konwersacji.
	///
	sf::Text historyText;

	///
	/// Kolejka dwukierunkowa przechowuj¹ca zmienne typu string; zapsuje ona historiê ca³ej konwersacji.
	///
	std::deque<std::string> history;
	
	///
	/// Przechowuje tekst wpisany przez klienta w oknie bufora konwersacji.
	///
	std::string buffer;

	///
	/// Funkcja polimorficzna okreœlaj¹ca wykonanie konkretnego dzia³ania z u¿yciem zmiennej typu string przekazanej do tej funcji, gdy zostanie wciœniêty klawisz Enter.
	///
	std::function<void(const std::string & s)> onEnter;

public:
	///
	/// Konstruktor wywo³ywany dla klasy ChatWindow.
	/// @param pos przechowuje wspó³rzêdne x i y matematycznego wektora.
	/// @param length okreœla d³ugoœæ, zmienn¹ x, dla matematycznego wektora.
	/// @param thickness okreœla gruboœæ obramowañ.
	/// @param charSize okreœla wielkoœæ wpisywanych znaków.
	/// @param historyLength okreœla wielkoœæ zapisywanej historii rozmowy.
	/// @param font okreœla czcionkê dla wyœwitlanych znaków.
	///
	ChatWindow(const sf::Vector2f pos, const float length, const float thickness, const int charSize, 
		const std::size_t historyLength, const sf::Font & font);

	///
	/// Destruktor wywo³ywany dla klasy ChatWindow.
	///
	~ChatWindow();

	///
	/// Metoda ustawiaj¹ca d³ugoœæ i treœæ tekstu do wyœwietlenia w oknie czatu na podstawie tekstu wpisanego w bufor. 
	///
	void update();

	/** Metoda wykonuj¹ca konkretne dzia³ania w zale¿noœci od pojawiaj¹cych siê w buforze znaków. 
	  * Jeœli u¿ytkownik wprowadzi znak "Enter", wpisania w buforze wiadomoœæ zostanie wys³ana.
	  * Jeœli u¿ytkownik wprowadzi znak "Backspace", z bufora zosatnie usuniêty ostatni znak.
	*/
	void handleEvent(sf::Event & event);

	///
	/// Metoda dodaj¹ca napisan¹ wiadomoœæ na pocz¹tek kolejki i usuwaj¹ca najstarsz¹ wiadomoœæ z kolejki, jeœli wielkoœæ historii zostanie przekroczona.
	///
	void push(const std::string & s);
	
	///
	/// Metoda wykorzystuj¹ca funkcjê polimorficzn¹, która realizuje po³¹czenie oraz wys³anie wiadomoœci wstêpnej, gdy zostanie wciœniêty klawisz Enter.
	///
	void connectOnEnter(std::function<void(const std::string & s)> func);

	///
	/// Metoda rysuj¹ca okno czatu o parametrach przekazanych w zmiennej window.
	///
	void draw(sf::RenderWindow & window);

	///
	/// Metoda ustawiaj¹ca kolor obramowañ okna.
	///
	void setOutlineColor(const sf::Color & color);
	
	///
	/// Metoda ustawiaj¹ca kolor wype³nienia okna.
	///
	void setFillColor(const sf::Color & color);

	///
	/// Metoda ustawiaj¹ca kolor znaków.
	///
	void setCharColor(const sf::Color & color);
};