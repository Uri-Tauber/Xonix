#include "Button.h"

Button::Button(int _x, int _y, sf::Color c, std::string _label)
	: x(_x), y(_y), color(c), label(_label)
{
	bodyButton.emplace(FileManager::get_tx(FileManager::BUTTON_TX));
	bodyButton->setColor(color);
	bodyButton->setPosition(sf::Vector2f(x, y));
	
	setUpText();
};

void Button::displayButton(sf::RenderWindow& win)
{
	if (bodyButton) win.draw(*bodyButton);
	if (buttonText) win.draw(*buttonText);
}

void Button::setUpText()
{
	buttonText.emplace(FileManager::get_ttl(FileManager::FONT_TTL), label, 55);
	buttonText->setFillColor(sf::Color(169, 179, 186));
	buttonText->setStyle(sf::Text::Bold);

	//center text
	sf::FloatRect textRect = buttonText->getLocalBounds();
	buttonText->setOrigin({textRect.size.x / 2, textRect.size.y / 2});
	buttonText->setPosition(sf::Vector2f(x + width / 2, y + (3 * height / 8)));

}

bool Button::checkIfButtonPressed(sf::RenderWindow& win)
{
	if (active && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && win.hasFocus())
	{
		sf::Vector2i mPos = sf::Mouse::getPosition(win);
		//AABB
		if (mPos.x >= x && mPos.x <= x + width && mPos.y >= y && mPos.y <= y + height)
			return true;
	}
	return false;
}
