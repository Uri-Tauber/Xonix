#include "InfoPanel.h"
#include <iostream>

InfoPanel::InfoPanel(int _x, int _y, int _w, int _h) : x(_x), y(_y), width(_w), height(_h)
{
	sf::Font& f = FileManager::get_ttl(FileManager::FONT_TTL);
	
	tLev.emplace(f, "", 60);
	tLev->setFillColor(sf::Color(127, 224, 227));
	tLev->setStyle(sf::Text::Bold);
	tLev->setPosition(sf::Vector2f(x + 50, y + height / 6));
	
	tHp.emplace(f, "", 60);
	tHp->setFillColor(sf::Color(127, 224, 227));
	tHp->setStyle(sf::Text::Bold);
	tHp->setPosition(sf::Vector2f(x + 350, y + height / 6));
	
	tComp.emplace(f, "", 60);
	tComp->setFillColor(sf::Color(127, 224, 227));
	tComp->setStyle(sf::Text::Bold);
	tComp->setPosition(sf::Vector2f(x + 750, y + height / 6));
}

void InfoPanel::setNewInfo(int level, int hp, double percent, double percent_needed)
{
	s_levels = std::to_string(level);
	s_hp = std::to_string(hp);

	s_completion = std::to_string(percent);
	if (s_completion.length() >= 4) {
		s_completion = s_completion.substr(0, 4);
	}

	std::string tmp_s_percent = std::to_string(percent_needed);
	if (tmp_s_percent.length() >= 4) {
		tmp_s_percent = tmp_s_percent.substr(0, 4);
	}

	s_completion += "%/" + tmp_s_percent + "%";
}

void InfoPanel::drawInfo(sf::RenderWindow & win) 
{
	if (tLev) {
		tLev->setString(prefix_levels + s_levels);
		win.draw(*tLev);
	}
	if (tHp) {
		tHp->setString(prefix_hp + s_hp);
		win.draw(*tHp);
	}
	if (tComp) {
		tComp->setString(prefix_completion + s_completion);
		win.draw(*tComp);
	}
}

void InfoPanel::setUpText(sf::Text& t, int offset_x)
{
	// Deprecated, using emplace in constructor now
}
