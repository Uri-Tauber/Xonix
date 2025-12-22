#ifndef MENU
#define MENU

#include <array>
#include <memory>
#include <optional>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "FileManager.h"
#include <chrono>

/// <summary>
/// Class that represents a main manu of the program
/// </summary>
class Menu 
{
	const static int width{ 1620 };
	const static int height{ 1100 };
	const std::array<std::string, 4> credits = { "Game created by: " ,"Adran Zareba" ,"as a project for Computer Programming IV lecture" ,"See more at: https://github.com/Eques72" };
	int status = 1; //1 - active, schow buttons, 2 - active, show credits, 0 - inactive
	std::array<bool, 3> menuChoices{ false,false,false }; //(active = 1, inactive = 0, exit game = false)
	bool demandedCredits = false;

	std::optional<sf::Sprite> backgroundSprite;
	std::array<std::unique_ptr<Button>,5> buttons;

	std::optional<sf::Text> menuText;
	std::optional<sf::Text> creditsText;

	static constexpr std::chrono::milliseconds holdTime{ 200 };
	std::chrono::time_point<std::chrono::steady_clock> timeStamp;

public:

	Menu();

	/// <summary>
	/// Method that draws all menu components
	/// </summary>
	/// <param name="win">Reference to window on which the box will be drawn</param>
	void displayMenu(sf::RenderWindow& win);
	
	/// <summary>
	/// Method checks state of all buttons and sets menu state accordingly
	/// </summary>
	/// <param name="win">Reference to window on which menu is being displayed</param>
	/// <returns>Returns three boolean values. They represent players choices. First tells if player wants to start a game, second if they want to load a saved game and play, third if aplication has to be closed (false if it has)</returns>
	std::array<bool, 3> menuLogic(sf::RenderWindow& win);

	/// <summary>
	/// Method displays menu's sub page, it has credits text displayed and "back" button 
	/// </summary>
	/// <param name="win">Reference to window on which menu is being displayed</param>
	void displayCredits(sf::RenderWindow& win);

	/// <summary>
	/// changes a boolean value "demandedCredits" based on given param
	/// </summary>
	void checkForDemand(bool creditsNeeded);

	/// <summary>
	/// When this function is called, it measured 200ms, then ends
	/// </summary>
	void waitFunction();

	/// <summary>
	/// Method sets up all needed parameters for SFML text.
	/// </summary>
	void setUpText();

	/// <summary>
	/// Method configures all buttons of the menu, first 4 sets as acitve, fifth as inactive
	/// </summary>
	void initializeButtons();

	/// <summary>
	/// Returns a status of the menu
	/// </summary>
	inline bool getStatus() 
	{
		return status;
	}
};


#endif // !MENU
