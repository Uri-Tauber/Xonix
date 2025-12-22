#include "Menu.h"

Menu::Menu()
{
	waitFunction();

	initializeButtons();
	setUpText();

	FileManager::swapBackgroundImage(1);

	backgroundSprite.emplace(FileManager::get_tx(FileManager::BACKGROUND_TX));
}

void Menu::setUpText() 
{
	menuText.emplace(FileManager::get_ttl(FileManager::FONT_TTL), "-  -  -  XONIX  -  -  -", 150);
	menuText->setFillColor(sf::Color(127, 224, 227));
	menuText->setStyle(sf::Text::Bold);

	//center text
	sf::FloatRect textRect = menuText->getLocalBounds();
	menuText->setOrigin({textRect.size.x / 2, textRect.size.y / 2});
	menuText->setPosition(sf::Vector2f(width / 2, 100));

	creditsText = menuText;
}

void Menu::initializeButtons()
{
	buttons[0] = std::make_unique<Button>((width / 2 - 300 - 50), height / 2 - 25 - 150, sf::Color(113, 114, 168), "Start");
	buttons[1] = std::make_unique<Button>((width / 2 + 50), height / 2 - 25 - 150, sf::Color(113, 114, 168), "Continue");
	buttons[2] = std::make_unique<Button>((width / 2 - 300 - 50), height / 2 + 25, sf::Color(113, 114, 168), "Credits");
	buttons[3] = std::make_unique<Button>((width / 2 + 50), height / 2 + 25, sf::Color(113, 114, 168), "Exit");
	buttons[4] = std::make_unique<Button>((0 + 50), 900 - 200, sf::Color(113, 114, 168), "Back");

	buttons[4]->setInactive();
}


void Menu::displayMenu(sf::RenderWindow& win)
{
	if (backgroundSprite) win.draw(*backgroundSprite);

	if (status == 1)
	{
		if (menuText) win.draw(*menuText);

		for (size_t i{ 0 }; i < buttons.size() - 1; i++)
			buttons[i]->displayButton(win);
	}
	else if (status == 2)
	{
		displayCredits(win);
	}
}


std::array<bool, 3> Menu::menuLogic(sf::RenderWindow& win)
{
	if (buttons[0]->checkIfButtonPressed(win)) //START
	{
		buttons[0]->setInactive();
		menuChoices = { 1,0,1 };
		status = 0;
	}
	if (buttons[1]->checkIfButtonPressed(win))  //CONTINUE
	{
		buttons[1]->setInactive();
		menuChoices = { 1,1,1 };
		status = 0;
	}
	if (buttons[2]->checkIfButtonPressed(win) || demandedCredits) //CREDITS
	{
		demandedCredits = false;
		for (size_t i{ 0 }; i < buttons.size() - 1; i++)
			buttons[i]->setInactive();
		buttons[4]->setActive();
		status = 2;
	}
	if (buttons[3]->checkIfButtonPressed(win)) //EXIT
	{
		buttons[3]->setInactive();
		menuChoices = { 0,0,0 };
		status = 0;
	}
	if (buttons[4]->checkIfButtonPressed(win)) //BACK
	{
		buttons[4]->setInactive();
		status = 1;
	}

	if (status == 1)
		for (size_t i{ 0 }; i < buttons.size() - 1; i++)
			buttons[i]->setActive();

	return menuChoices;
}



void Menu::displayCredits(sf::RenderWindow& win)
{
	if (!creditsText) return;
	creditsText->setCharacterSize(80);
	creditsText->setString(credits[0]);
	creditsText->setPosition(sf::Vector2f(width / 2, 200));
	win.draw(*creditsText);

	creditsText->setString(credits[1]);
	creditsText->setPosition(sf::Vector2f(width / 2, 300));
	win.draw(*creditsText);

	creditsText->setCharacterSize(40);
	creditsText->setString(credits[2]);
	creditsText->setPosition(sf::Vector2f(width / 2, 390));
	win.draw(*creditsText);

	creditsText->setString(credits[3]);
	creditsText->setPosition(sf::Vector2f(width / 2, 600));
	win.draw(*creditsText);

	buttons[4]->displayButton(win);
}

void Menu::waitFunction() 
{
	bool hold = true;
	timeStamp = std::chrono::steady_clock::now();

	while (hold)
		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - timeStamp) >= holdTime)
			hold = false;
}

void Menu::checkForDemand(bool creditsNeeded) 
{
	demandedCredits = creditsNeeded;
}