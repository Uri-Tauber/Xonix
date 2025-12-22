#ifndef BUT
#define BUT

#include <memory>
#include <optional>
#include <SFML/Graphics.hpp>
#include "FileManager.h"

/// <summary>
/// Class represents a button that has a label and background inage, can be pressed using left mouse button
/// </summary>
class Button
{
	int x{ 0 };
	int y{ 0 };

	const int width{ 300 };
	const int height{ 150 };
	std::string label{"BUTTON"};

	bool active = true;
	sf::Color color = sf::Color::White;

	std::optional<sf::Sprite> bodyButton;
	std::optional<sf::Text> buttonText;

public:

	Button(int _x, int _y, sf::Color c, std::string _label);

	/// <summary>
	/// Method draws button elements on the window
	/// </summary>
	void displayButton(sf::RenderWindow& win);
	
	/// <summary>
	/// Sets up SFML text parameters 
	/// </summary>
	void setUpText();

	/// <summary>
	/// Method checks button statement (basing on mouse state and position in relation to window and button)
	/// </summary>
	/// <returns> returns true if button was pressed</returns>
	bool checkIfButtonPressed(sf::RenderWindow& win);

	/// <summary>
	/// Sets button active (can be pressed)
	/// </summary>
	inline void setActive() 
	{
		active = true;
	}

	/// <summary>
	/// Sets button inactive (can not be pressed)
	/// </summary>
    inline void setInactive() 
	{
		active = false;
	}
};


#endif // !BUT
