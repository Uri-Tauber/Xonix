#include "KeyboardImput.h"

KeyboardImput::KeyboardImput(std::shared_ptr<Player> p) : player(p) {}

void KeyboardImput::setPlayer(std::shared_ptr<Player> p) { player = p; }

void KeyboardImput::checkKeyboardImput(bool& activatePause)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
		activatePause = true;
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
			player->planNextTurn(0, -1, 270);

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
			player->planNextTurn(0, 1, 90);

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			player->planNextTurn(-1, 0, 180);

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			player->planNextTurn(1, 0, 0);
	}
}