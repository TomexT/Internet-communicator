#include "Window.h"
#include <iostream>

ChatWindow::ChatWindow(const sf::Vector2f pos, const float length_l, const float thickness_l,
	const int charSize_l, const std::size_t historyLength_l, const sf::Font & font) :
	length(length_l), thickness(thickness_l), charSize(charSize_l), historyLength(historyLength_l),
	historyBox(sf::Vector2f(length, thickness * historyLength + charSize * historyLength)),
	bufferBox(sf::Vector2f(length, thickness * 2 + charSize))
{
	historyBox.setPosition(pos);
	float x2 = historyBox.getGlobalBounds().left;
	float y2 = historyBox.getGlobalBounds().top + historyBox.getGlobalBounds().height + 3 * thickness;
	bufferBox.setPosition(x2, y2);

	historyBox.setOutlineThickness(thickness);
	bufferBox.setOutlineThickness(thickness);

	text.setFont(font);
	text.setCharacterSize(charSize);
	text.setPosition(x2 + thickness, y2 + thickness);

	historyText.setFont(font);
	historyText.setCharacterSize(charSize);
}

ChatWindow::~ChatWindow() {}

void ChatWindow::update()
{
	text.setString(buffer);
}

void ChatWindow::handleEvent(sf::Event & event)
{
	if (event.type == sf::Event::TextEntered)
	{
		char code = static_cast<char>(event.text.unicode);

		if (event.text.unicode == 13) //enter
		{
			onEnter(buffer);
			buffer.clear();
		}

		else if (code != '\b') //backspace
			buffer.push_back(code);
		else if (code == '\b')
		{
			if (buffer.size() > 0)
				buffer.pop_back();
		}
	}
}

void ChatWindow::push(const std::string & s)
{
	if (s.size() > 0)
	{
		history.push_front(s);
		if (history.size() > historyLength)
			history.pop_back();
	}
}

void ChatWindow::connectOnEnter(std::function<void(const std::string & s)> func)
{
	onEnter = func;
}

void ChatWindow::draw(sf::RenderWindow & window)
{
	window.draw(historyBox);
	window.draw(bufferBox);
	window.draw(text);

	float x = historyBox.getGlobalBounds().left + 2 * thickness;
	float y = historyBox.getGlobalBounds().top + historyBox.getGlobalBounds().height - thickness - charSize;

	for (std::size_t i = 0; i < history.size(); ++i)
	{
		historyText.setString(history[i]);
		historyText.setPosition(x, y - i * charSize - i * thickness - thickness);
		window.draw(historyText);
	}
}

void ChatWindow::setOutlineColor(const sf::Color & color)
{
	historyBox.setOutlineColor(color);
	bufferBox.setOutlineColor(color);
}

void ChatWindow::setFillColor(const sf::Color & color)
{
	historyBox.setFillColor(color);
	bufferBox.setFillColor(color);
}

void ChatWindow::setCharColor(const sf::Color & color)
{
	text.setFillColor(color);
	historyText.setFillColor(color);
}