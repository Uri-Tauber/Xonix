#include "FileManager.h"

std::unique_ptr<sf::Texture> FileManager::player_tx = nullptr;
std::unique_ptr<sf::Texture> FileManager::blue_enemy_tx = nullptr;
std::unique_ptr<sf::Texture> FileManager::green_enemy_tx = nullptr;
std::unique_ptr<sf::Texture> FileManager::background_tx = nullptr;
std::unique_ptr<sf::Texture> FileManager::wall_tx = nullptr;
std::unique_ptr<sf::Texture> FileManager::button_tx = nullptr;
std::unique_ptr<sf::Font> FileManager::font_ttl = nullptr;

int FileManager::chosedBackground = 1;

void FileManager::setUpResources()
{
	static bool initialized = false;
	if (initialized) return;
	initialized = true;

	std::filesystem::path resourcesDir = "resources";

	player_tx = std::make_unique<sf::Texture>();
	player_tx->loadFromImage(openImage(resourcesDir / "player.png"));

	blue_enemy_tx = std::make_unique<sf::Texture>();
	blue_enemy_tx->loadFromImage(openImage(resourcesDir / "enemy.png"));

	green_enemy_tx = std::make_unique<sf::Texture>();
	green_enemy_tx->loadFromImage(openImage(resourcesDir / "enemyHunt.png"));

	background_tx = std::make_unique<sf::Texture>();
	background_tx->loadFromImage(openImage(resourcesDir / "menuImg.png"));
	chosedBackground = 1;

	wall_tx = std::make_unique<sf::Texture>();
	wall_tx->loadFromImage(openImage(resourcesDir / "Wall.png"));

	button_tx = std::make_unique<sf::Texture>();
	button_tx->loadFromImage(openImage(resourcesDir / "button.png"));

	font_ttl = std::make_unique<sf::Font>();
	font_ttl->openFromFile(resourcesDir / "DIGIB.TTF");
}

void FileManager::resetResources()
{
	player_tx.reset();
	blue_enemy_tx.reset();
	green_enemy_tx.reset();
	background_tx.reset();
	wall_tx.reset();
	button_tx.reset();
	font_ttl.reset();
}

void FileManager::swapBackgroundImage(int swap)
{
	std::filesystem::path resourcesDir = "resources";
	if (chosedBackground == 1 && swap == 0)
	{
		background_tx->loadFromFile(resourcesDir / "BgPic.png");
		chosedBackground = 0;
	}
	else if(chosedBackground == 0 && swap == 1)
	{
		background_tx->loadFromFile(resourcesDir / "menuImg.png");
		chosedBackground = 1;
	}
}

sf::Texture& FileManager::get_tx(int type)
{
	switch (type)
	{
	case PLAYER_TX:
		if (player_tx) return *player_tx.get();
		break;
	case BLUE_ENEMY_TX:
		if (blue_enemy_tx) return *blue_enemy_tx.get();
		break;
	case GREEN_ENEMY_TX:
		if (green_enemy_tx) return *green_enemy_tx.get();
		break;
	case BUTTON_TX:
		if (button_tx) return *button_tx.get();
		break;
	case BACKGROUND_TX:
		if (background_tx) return *background_tx.get();
		break;
	case WALL_TX:
		if (wall_tx) return *wall_tx.get();
		break;
	default:
		break;
	}

	static sf::Texture t;
	return t;
}

sf::Font& FileManager::get_ttl(int type)
{
	switch (type)
	{
	case FONT_TTL:
		if (font_ttl) {
			return *font_ttl.get();
		}
		break;
	default:
		break;
	}

	static sf::Font f;
	return f;
}

sf::Image FileManager::openImage(std::filesystem::path path)
{
	sf::Image i;
	try
	{
		if (!checkDir(path))
			throw(std::string("Unable to find image under path: " + path.string() + " \n"));

		i.loadFromFile(path);
	
		return i;
	}
	catch (std::string& e)
	{
		std::cout << e;
	}
	return i;
}

void FileManager::openTTFfile(sf::Font& f, std::filesystem::path path)
{
	try
	{
		if (!checkDir(path))
			throw(std::string("Unable to find TTF file under path: " + path.string() + " \n"));

		f.openFromFile(path);
	}
	catch (std::string& e)
	{
		std::cout << e;
	}
}

void FileManager::readFromFile(std::string& contener, std::filesystem::path path)
{
	std::ifstream stream(path);
	try
	{
		if (!stream.is_open())
			throw(std::string("Unable to read file from path: " + path.string() + "\n"));

		std::string tmp;
		while (std::getline(stream, tmp)) {
			if (!tmp.empty() && tmp.back() == '\r')
				tmp.pop_back();
			contener += tmp;
		}

		stream.close();
	}
	catch (std::string& e)
	{
		std::cout << e;
	}
}

void FileManager::readFromFile(std::vector<std::string>& contener, std::filesystem::path path)
{
	std::ifstream stream(path);
	try
	{
		if (!stream.is_open())
			throw(std::string("Unable to read file from path: " + path.string() + "\n"));


		std::string tmp;
		while (std::getline(stream, tmp)) {
			if (!tmp.empty() && tmp.back() == '\r')
				tmp.pop_back();
			contener.push_back(tmp);
		}

		stream.close();
	}
	catch (std::string& e)
	{
		std::cout << e;
	}
}

void FileManager::readMapFile(std::array<int, 1620>& a, std::filesystem::path path)
{
	std::string tmp;
	int aIndex = 0;

	readFromFile(tmp, path);
	tmp.shrink_to_fit();

	if (!validateMap(tmp))
		for (int q{ 0 }; q < tmp.size(); q++)
			if (tmp[q] != '0' && tmp[q] != '1' && tmp[q] != ',')
				tmp[q] = '0';

	for (int q{ 0 }; q < tmp.size(); q++)
	{
		if (aIndex >= 1620) break;
		switch (tmp[q])
		{
		case '1':
			a[aIndex] = 1;
			++aIndex;
			break;
		case '0':
			a[aIndex] = 0;
			++aIndex;
			break;
		case ',':
			break;
		default:
			break;
		}
	}
}

void FileManager::readLevelsFile(std::vector<std::string>& l, std::filesystem::path path)
{
	readFromFile(l, path);

	try
	{
		if (!validateLevels(l))
		{
			l.clear(); // Clear invalid data
			std::string s{ "Can not read game settings properly, reinstall game \n" };
			throw(s);
		}
	}
	catch (std::string& e)
	{
		std::cout << e;
	}
}

bool FileManager::validateLevels(std::vector<std::string>& l)
{
	std::regex r1("[0-9][0-9];");
	std::regex r2("[0-9]{1,2};[0-9]{2};[0-5];[0-5];[0-5];[0-5];[0-5];");
	std::smatch mS;
	
	if (l.empty()) return false;

	if (std::regex_match(l[0], r1))
	{
		for (int q = 0; q < std::stoi(l[0]); q++) {
			if (q + 1 >= l.size()) return false;
			if (!std::regex_match(l[q + 1], r2)) return false;
		}

		return true;
	}
	return false;
}

bool FileManager::createFile(std::filesystem::path path, std::string name, std::string content)
{
	std::filesystem::path fullPath = path / name;
	if (!std::filesystem::exists(fullPath))
	{
		std::ofstream stream(fullPath);

		stream << content;

		stream.close();
		return true;
	}
	return false;
}

bool FileManager::createFile(std::filesystem::path path, std::string name, std::vector<std::string> contents)
{
	std::filesystem::path fullPath = path / name;
	if (!std::filesystem::exists(fullPath))
	{
		std::ofstream stream(fullPath);

		for (auto c : contents)
			stream << c << '\n';

		stream.close();
		return true;
	}
	return false;
}

bool FileManager::validateMap(std::string mS)
{
	std::regex r("[01,]+");

	if (std::regex_match(mS, r))
		return true;
	return false;
}

bool FileManager::validateSaves(std::vector<std::string> sav)
{
	std::regex r("[0-5]\n[0-9]{1,2}\n");
	std::string s;
	for (auto a : sav)
		s += a+"\n";

	if (std::regex_match(s, r))
		return true;
	return false;
}

bool FileManager::editFile(std::filesystem::path path, std::vector<std::string> contents)
{
	if (std::filesystem::exists(path))
	{
		std::ofstream stream(path);

		for (auto c : contents)
			stream << c << '\n';

		stream.close();
		return true;
	}
	return false;
}

bool FileManager::editFile(std::filesystem::path path, std::string content)
{
	if (std::filesystem::exists(path))
	{
		std::ofstream stream(path);

		stream << content;

		stream.close();

		return true;
	}
	return false;
}

bool FileManager::checkDir(std::filesystem::path path)
{
	return std::filesystem::exists(path);
}

bool FileManager::createDir(std::filesystem::path path, std::string name)
{
	std::filesystem::path fullPath = path / name;
	if (!checkDir(fullPath))
	{
		std::filesystem::create_directory(fullPath);
		return true;
	}
	return false;
}