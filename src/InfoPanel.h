#ifndef INFO_P
#define INFO_P

#include <memory>
#include <string>
#include <optional>
#include <SFML/Graphics.hpp>
#include "FileManager.h"

/// <summary>
/// Info panel is a panel that is displayed bellow the running game map. Gives information of currend game state
/// </summary>
class InfoPanel
{
	std::string prefix_levels{"Level: "};
	std::string prefix_hp{ "Lives left: " };
	std::string prefix_completion{ "Level completion: " };

	std::string s_levels;
	std::string s_hp;
	std::string s_completion;

	std::optional<sf::Text> tLev;
	std::optional<sf::Text> tHp;
	std::optional<sf::Text> tComp;

	int x;
	int y;
	int width;
	int height;

	/// <summary>
	/// Method sets up all needed parameters for SFML text.
	/// </summary>
	/// <param name="text">Reference to configured text</param>
	/// <param name="offset_x">Tells how much this text has to be moved horizontaly in relation to x coordinate of the panel</param>
	void setUpText(sf::Text& t, int offset_x);

public:

	InfoPanel(int _x, int _y, int _w, int _h);

	/// <summary>
	/// actualizes information displayed on the panel	/// </summary>
	/// <param name="level">current level</param>
	/// <param name="hp">players hitpoints</param>
	/// <param name="percent">percentage of level completion</param>
	/// <param name="percent_needed">percentage needed to pass a level</param>
	void setNewInfo(int level, int hp, double percent, double percent_needed);

	/// <summary>
	/// Method draws all elements of info panel
	/// </summary>
	/// <param name="win">Reference to window on which the box will be drawn</param>
	void drawInfo(sf::RenderWindow& win);

};

#endif //INFO_P

