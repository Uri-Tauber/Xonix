#include "GWindow.h"

void GWindow::config()
{
	window.create(sf::VideoMode({static_cast<unsigned int>(width), static_cast<unsigned int>(height)}), "Pac-xon!", sf::Style::Close);
	window.setPosition(sf::Vector2i(0, 0));
	window.setFramerateLimit(60);

	setGameIcon();
}

void GWindow::setGameIcon()
{
	sf::Image icon;
	icon = FileManager::openImage(std::filesystem::path("resources") / "Logo.png");
	window.setIcon(icon);
}

GWindow::GWindow()
{
	config();
}

sf::RenderWindow& GWindow::getWindow() { return window; }

void GWindow::deleteMenu()
{
	menu.release();
}

void GWindow::setMenu() 
{
	menu = std::make_unique<Menu>();
	menu->checkForDemand(this->demandCredits);
	demandCredits = false;
}

std::array<bool, 3> GWindow::displayMenu()
{
	std::array<bool, 3> choices{0,0,0};
	while (window.isOpen() && menu->getStatus() != 0)
	{
		while (const auto event = window.pollEvent())
			if (event->is<sf::Event::Closed>())
				window.close();

		choices = menu->menuLogic(window);

		window.clear();
			menu->displayMenu(window);
		window.display();

	}

	menu.reset();
	return choices;
}

void GWindow::setInfoPanel(int _x, int _y, int _w, int _h) 
{
	iP = std::make_unique<InfoPanel>(_x,_y,_w,_h);
	iP->setNewInfo(0, 0, 0.0, 0.0);
}

void GWindow::displayInfoPanel(int level, int hp, double percent, double percent_needed)
{
	iP->setNewInfo(level, hp, percent, percent_needed);
	iP->drawInfo(this->window);
}

void GWindow::setVictoryBox()
{
	tB = std::make_unique<TextBox>(width / 2 - 600, height / 2 - 350, 1200, 500, "Congratulations!", "You have won the game :D", "To credits");
	tB->turnFrame(true);
	tB->fillFrame(true);
}

void GWindow::setDefeatBox() 
{
	tB = std::make_unique<TextBox>(width / 2 - 400, height / 2 - 350, 800, 500, "You Lose!", "press back to return to menu");
	tB->turnFrame(true);
}
void GWindow::setPauseBox() 
{
	tB = std::make_unique<TextBox>(width / 2 - 350, height / 2 - 300, 700, 400, "Pause", " ", "Back", "Save & Quit");
	tB->turnFrame(false);
}

std::pair<bool, int> GWindow::getTextBoxResponse()
{
	std::pair respond = tB->waitForButton(this->window);
	if (!respond.first)
	{
		tB.release();

		return std::make_pair(false, respond.second);
	}
	return std::make_pair(true, respond.second);


}

void GWindow::displayTextBox()
{
	tB->displayTextBox(this->window);
}
