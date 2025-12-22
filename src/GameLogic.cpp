#include "GameLogic.h"

void GameLogic::start()
{
	FileManager::setUpResources();

	while (isMenuActive)
	{
		winG.setMenu();

		std::array<bool, 3> menuChoices = winG.displayMenu();
		isMenuActive = menuChoices[2];
	
		winG.deleteMenu();

		gameOver = false;
		isPauseActive = false;
		isDefeatBoxActive = false;
		nextLevelIndex = 2;
		currentLevelIndex = 1;

		if (menuChoices[0])
		{
			if (initializeGame(menuChoices[1]))
			{
				run();
			}
		}
	}
}

bool GameLogic::initializeGame(bool doLoadGame)
{
	player = std::make_shared<Player>(6);
	map = std::make_unique<Map>();
	hitPoints = 3;

	kI.setPlayer(player);

	std::thread readThread(FileManager::readLevelsFile, std::ref(levels), std::filesystem::path("resources") / "gameSettings" / "levels.txt");

	if (doLoadGame)
		loadGame();

	readThread.join();

	if (levels.empty()) {
		std::cerr << "Failed to load levels. Exiting initialization." << std::endl;
		return false;
	}

	prepareNextLevel(currentLevelIndex);
	setUpNextLevel();

	if (currentLevelIndex < 20) {
		nextLevelLoader = std::thread(&GameLogic::prepareNextLevel, this, nextLevelIndex);
	}

	winG.setInfoPanel(0, 900, winG.width, winG.height - 900);
	return true;
}

void GameLogic::run()
{
	while (!gameOver && winG.getWindow().isOpen())
	{
		while (const auto event = winG.getWindow().pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				saveGame();
				winG.getWindow().close();
			}
		}

	///////////////////////////////////////////////////////////////////
		
		handleEvents();
	
	///////////////////////////////////////////////////////////////////
		winG.getWindow().clear();
		{
			drawPanels();
			drawEntities();
		}
		winG.getWindow().display();
	}
}

void GameLogic::drawPanels() 
{
	if (!map) return;
	map->draw(winG.getWindow());
	winG.displayInfoPanel(currentLevelIndex, hitPoints, map->getProggres(), levelInfo[1]);

	if (isPauseActive || isDefeatBoxActive || isGameCompleted)
		winG.displayTextBox();
}

void GameLogic::drawEntities()
{
	if (!player) return;
	player->draw(winG.getWindow());

	for (size_t q = 0; q < enemies.size(); q++)
		enemies[q]->draw(winG.getWindow());
}

void GameLogic::handleEvents()
{
	//check for ESC or P keys to be pressed (activates pause)
	kI.checkKeyboardImput(isPauseActive);
	if (isPauseActive && winG.pasuseBoxInitialized == false)
	{
		winG.setPauseBox();
		winG.pasuseBoxInitialized = true;	
	}

	//(If none of text boxes are active proced with game logic
	if (!isDefeatBoxActive && !isPauseActive && !isGameCompleted)
	{
		handleGameConditions();
		calculateLogic();
	}

	if ((isDefeatBoxActive || isGameCompleted) && !winG.getTextBoxResponse().first)
	{
		isDefeatBoxActive = false;	isGameCompleted = false; gameOver = true;
		currentLevelIndex = 1;	nextLevelIndex = 2;	hitPoints = 3;
		saveGame();

		if (nextLevelLoader.joinable())
			nextLevelLoader.join();
		nextLevelEnemies.clear();

		winG.demandCredits = true;
	}

	if (isPauseActive)
	{
		std::pair response = winG.getTextBoxResponse();
		if (!response.first)
		{
			if (response.second == 1)
			{
				gameOver = true;
				if (nextLevelLoader.joinable())
					nextLevelLoader.join();
				nextLevelEnemies.clear();

				saveGame();
			}
			isPauseActive = false;
			winG.pasuseBoxInitialized = false;
		}
	}
}

void GameLogic::handleGameConditions()
{
	map->updateCrumbling();

	if (checkLivesLossConditions())
		deathProc();

	if (checkLevelCompletion())
		nextLevelProc();
}

bool GameLogic::checkLivesLossConditions()
{
	for (int q = 0; q < enemies.size(); q++)
		if (enemies[q]->checkEntityCollisions(*player)) return true;

	if (player->checkTailCollisons(*map).first) return true;

	return false;
}

void GameLogic::deathProc()
{
	hitPoints--;
	if (hitPoints <= 0)
	{
		winG.setDefeatBox();
		isDefeatBoxActive = true;
	}
	else
	{
		player->revivePlayer();
		map->clearTail();
	}
}

bool GameLogic::checkLevelCompletion()
{
	if (map->getProggres() >= levelInfo[1]) return true;
	return false;
}

void GameLogic::nextLevelProc()
{
	currentLevelIndex++;
	nextLevelIndex++;

	if (currentLevelIndex >= maxLevels)
	{
		winG.setVictoryBox();
		isGameCompleted = true;
	}
	else
	{
		if (nextLevelLoader.joinable())
			nextLevelLoader.join();
		setUpNextLevel();
		nextLevelLoader = std::thread(&GameLogic::prepareNextLevel, this, nextLevelIndex);
	}
}

void GameLogic::setUpNextLevel()
{
	levelInfo = nextLevelInfo;
	if (player) player->revivePlayer();
	if (map) map->resetMap();

	enemies.clear();
	enemies = nextLevelEnemies;
	nextLevelEnemies.clear();
}

void GameLogic::getLevelInformation(int index)
{
	std::string lvlStr = levels[index];
	std::string tmpNum = "";
	nextLevelInfo.clear();

	for (auto c : lvlStr)
	{
		if (c != ';') tmpNum += c;
		else
		{
			nextLevelInfo.push_back(std::stoi(tmpNum));
			tmpNum = "";
		}
	}
}

void GameLogic::prepareNextLevel(int lvlIndex)
{
	getLevelInformation(lvlIndex);

	for (int q = 0; q < nextLevelInfo[2]; q++)
		nextLevelEnemies.push_back(std::make_shared<DefaultEnemy>(500 + q * 30, 500, 3));

	for (int q = 0; q < nextLevelInfo[3]; q++)
		nextLevelEnemies.push_back(std::make_shared<DestroyerEnemy>(500, 500, 2));

	for (int q = 0; q < nextLevelInfo[4]; q++)
		nextLevelEnemies.push_back(std::make_shared<HunterEnemy>(0, 0, 2, player));

}

void GameLogic::calculateLogic()
{
	player->move(*map);

	std::vector<std::thread> threads;

	if (player->getConquestState())
	{
		std::vector<int> t;
		for (int q = 0; q < enemies.size(); q++)
			t.push_back(enemies[q]->getIndexOfTile());
		conquer(t);
	}

	for (int q = 0; q < enemies.size(); q++)
	{
		threads.emplace_back(&Enemy::move, enemies[q].get(), std::ref(*map));
		std::pair<bool, int> result = enemies[q]->checkTailCollisons(*map);
		if (result.first) map->startCrumbling(result.second);
	}
	for (auto& t : threads)
		t.join();
}

void GameLogic::drop(int XY)
{
	if (map->getTileState(XY) == 0) map->changeTileState(XY, -1);
	if (map->getTileState(XY - Map::MAP_WIDTH) == 0) drop(XY - Map::MAP_WIDTH);
	if (map->getTileState(XY + Map::MAP_WIDTH) == 0) drop(XY + Map::MAP_WIDTH);
	if (map->getTileState(XY - 1) == 0) drop(XY - 1);
	if (map->getTileState(XY + 1) == 0) drop(XY + 1);
}

void GameLogic::conquer(std::vector<int> positions)
{
	for (auto a : positions)
		drop(a);

	map->fillEmptySpace();

	player->conquestPossible = false;
}

GameLogic::~GameLogic()
{
	FileManager::resetResources();

	if (nextLevelLoader.joinable()) {
		nextLevelLoader.join();
	}
}

void GameLogic::saveGame()
{
	std::vector<std::string> contents;
	contents.push_back(std::to_string(currentLevelIndex));
	contents.push_back(std::to_string(hitPoints));
	FileManager::editFile(std::filesystem::path("resources") / "Saves" / "gameSave.txt", contents);
}

void GameLogic::loadGame()
{
	std::vector<std::string> data;
	FileManager::readFromFile(data, std::filesystem::path("resources") / "Saves" / "gameSave.txt");
	if (data.size() >= 2)
	{
		currentLevelIndex = std::stoi(data[0]);
		nextLevelIndex = currentLevelIndex + 1;
		hitPoints = std::stoi(data[1]);
	}
}
