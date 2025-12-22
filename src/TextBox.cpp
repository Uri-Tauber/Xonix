#include "TextBox.h"

TextBox::TextBox(int _x, int _y, int _w, int _h, std::string _text, std::string _subtext)
{
	text.emplace(FileManager::get_ttl(FileManager::FONT_TTL), _text, 150);
	text->setFillColor(sf::Color(100, 200, 200));
	text->setStyle(sf::Text::Bold);
	sf::FloatRect textRect = text->getLocalBounds();
	text->setOrigin({textRect.size.x / 2, textRect.size.y / 2});
	text->setPosition(sf::Vector2f(_x + _w/2, _y + _h / 8));

	subtext.emplace(FileManager::get_ttl(FileManager::FONT_TTL), _subtext, 55);
	subtext->setFillColor(sf::Color(100, 200, 200));
	subtext->setStyle(sf::Text::Bold);
	sf::FloatRect subtextRect = subtext->getLocalBounds();
	subtext->setOrigin({subtextRect.size.x / 2, subtextRect.size.y / 2});
	subtext->setPosition(sf::Vector2f(_x + _w / 2, _y + _h / 2));

	setUpFrame(_x,_y,_w,_h);

	buttons.emplace_back(std::make_unique<Button>(_x - 150 + _w / 2, _y + _h - 150, sf::Color(113, 114, 168), "Back"));
	buttons[0]->setActive();
}

TextBox::TextBox(int _x, int _y, int _w, int _h, std::string _text, std::string _subtext, std::string buttonLabel)
{
	text.emplace(FileManager::get_ttl(FileManager::FONT_TTL), _text, 150);
	text->setFillColor(sf::Color(100, 200, 200));
	text->setStyle(sf::Text::Bold);
	sf::FloatRect textRect = text->getLocalBounds();
	text->setOrigin({textRect.size.x / 2, textRect.size.y / 2});
	text->setPosition(sf::Vector2f(_x + _w / 2, _y + _h / 8));

	subtext.emplace(FileManager::get_ttl(FileManager::FONT_TTL), _subtext, 55);
	subtext->setFillColor(sf::Color(100, 200, 200));
	subtext->setStyle(sf::Text::Bold);
	sf::FloatRect subtextRect = subtext->getLocalBounds();
	subtext->setOrigin({subtextRect.size.x / 2, subtextRect.size.y / 2});
	subtext->setPosition(sf::Vector2f(_x + _w / 2, _y + _h / 2));

	setUpFrame(_x, _y, _w, _h);

	buttons.emplace_back(std::make_unique<Button>(_x - 150 + _w / 2, _y + _h - 150, sf::Color(113, 114, 168), buttonLabel));
	buttons[0]->setActive();
}

TextBox::TextBox(int _x, int _y, int _w, int _h, std::string _text, std::string _subtext, std::string buttonLabel1, std::string buttonLabel2)
{
	text.emplace(FileManager::get_ttl(FileManager::FONT_TTL), _text, 150);
	text->setFillColor(sf::Color(100, 200, 200));
	text->setStyle(sf::Text::Bold);
	sf::FloatRect textRect = text->getLocalBounds();
	text->setOrigin({textRect.size.x / 2, textRect.size.y / 2});
	text->setPosition(sf::Vector2f(_x + _w / 2, _y + _h / 8));

	subtext.emplace(FileManager::get_ttl(FileManager::FONT_TTL), _subtext, 55);
	subtext->setFillColor(sf::Color(100, 200, 200));
	subtext->setStyle(sf::Text::Bold);
	sf::FloatRect subtextRect = subtext->getLocalBounds();
	subtext->setOrigin({subtextRect.size.x / 2, subtextRect.size.y / 2});
	subtext->setPosition(sf::Vector2f(_x + _w / 2, _y + _h / 2));

	setUpFrame(_x, _y, _w, _h);

	buttons.emplace_back(std::make_unique<Button>(_x - 150 + _w / 4, _y + _h - 150, sf::Color(113, 114, 168), buttonLabel1));
	buttons.emplace_back(std::make_unique<Button>(_x - 150 + 3 * _w / 4, _y + _h - 150, sf::Color(113, 114, 168), buttonLabel2));
	buttons[0]->setActive();
	buttons[1]->setActive();
}

void TextBox::setUpText(sf::Text& t, std::string s, float textSize)
{
	// This method is now deprecated/unused since we use emplace in constructor
	// Left for compatibility
}

void TextBox::setUpFrame(int _x, int _y, int _w, int _h)
{
	frame.setPosition(sf::Vector2f(_x, _y));
	frame.setOutlineColor(sf::Color(100, 200, 200));
	frame.setOutlineThickness(15.f);
	frame.setSize(sf::Vector2f(_w, _h));
	frame.setFillColor(sf::Color::Transparent);
}

void TextBox::turnFrame(bool on_off)
{
	useFrame = on_off;
}

void TextBox::fillFrame(bool on_off)
{
	fullFrame = true;
}

void TextBox::displayTextBox(sf::RenderWindow& win)
{
	if (useFrame)
	{
		if (fullFrame && frame.getFillColor() == sf::Color::Transparent)
			frame.setFillColor(sf::Color(60, 90, 90));
		win.draw(frame);
	}
	if (text) win.draw(*text);
	if (subtext) win.draw(*subtext);

	for(size_t q{0}; q < buttons.size(); q++)
		buttons[q]->displayButton(win);
}

std::pair<bool, int>  TextBox::waitForButton(sf::RenderWindow& win)
{
	int index = -1;

	if (buttons[0]->checkIfButtonPressed(win))
	{
		index = 0;
		isActive = false;
	}
	else if (buttons.size() > 1 && buttons[1]->checkIfButtonPressed(win))
	{
		index = 1;
		isActive = false;
	}
	return std::make_pair(isActive, index);
}