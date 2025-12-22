#include "Map.h"
#include <algorithm>
#include <iostream>

void Map::createBackground()
{
	FileManager::swapBackgroundImage(0);

	backgroundSprite.emplace(FileManager::get_tx(FileManager::BACKGROUND_TX));
	backgroundSprite->setPosition(sf::Vector2f(0.f, 0.f));
}
void Map::draw(sf::RenderWindow& win) const
{
	if (backgroundSprite) win.draw(*backgroundSprite);

	sf::Texture& wallTex = FileManager::get_tx(FileManager::WALL_TX);
	sf::Sprite sprite(wallTex);
	sprite.setTextureRect(sf::IntRect({0, 0}, {30, 30}));

	int lastDrawnType = Map::WALL_TILE;

	for (int q{ 0 }; q < MAP_HEIGHT; q++)
	{
		for (int w{ 0 }; w < MAP_WIDTH; w++)
		{
			float x = (float)w * 30;
			float y = (float)q * 30;
			sprite.setPosition(sf::Vector2f(x, y));


			switch (mapping[w + q * MAP_WIDTH])
			{
			case Map::WALL_TILE:
				if (lastDrawnType != Map::WALL_TILE)
					sprite.setTextureRect(sf::IntRect({0, 0}, {30, 30}));

				win.draw(sprite);
				lastDrawnType = Map::WALL_TILE;
				break;
			case Map::TAIL_TILE:
				if (lastDrawnType != Map::TAIL_TILE)
					sprite.setTextureRect(sf::IntRect({30, 0}, {30, 30}));
				
				win.draw(sprite);
				lastDrawnType = Map::TAIL_TILE;
				break;
			case 3: //crumbling tiles up to 6
			case 4:
			case 5:
			case 6:
					sprite.setTextureRect(sf::IntRect({30* mapping[w + q * MAP_WIDTH]-1, 0}, {30, 30}));
				win.draw(sprite);
				lastDrawnType = 3;
				break;
			default:
				break;

			}
		}
	}

}

Map::Map()
{
	createBackground();
}


int Map::getTileState(int index)
{
	if (index < mapping.size())
		return mapping[index];
	return -1;
}

void Map::clearTail()
{
	auto d = [](int n) {return n >= TAIL_TILE ? EMPTY_TILE : n; };
	std::ranges::transform(mapping, mapping.begin(), d);
}

void Map::fillEmptySpace()
{
	auto c = [](int n) {return n >= 3 ? OCCUPIED_TILE : n; };
	auto d = [](int n) {return n == OCCUPIED_TILE ? EMPTY_TILE : WALL_TILE; };
	std::ranges::transform(mapping, mapping.begin(), c);
	std::ranges::transform(mapping, mapping.begin(), d);
}

void Map::changeTileState(int index, int newState) { mapping[index] = newState; }

double Map::getProggres()
{
	auto i = std::ranges::count(mapping, Map::WALL_TILE);
	return (((double)i / (double)mapping.size()) * 100.0);
}

void Map::resetMap()
{
	FileManager::readMapFile(mapping, "resources/gameSettings/map.txt");
}


bool Map::isTileInOuterRing(int index)
{
	if (index >= 0 && index < Map::MAP_WIDTH)
		return true;
	if (index >= Map::MAP_WIDTH * (Map::MAP_HEIGHT - 1) && index < Map::MAP_WIDTH * Map::MAP_HEIGHT)
		return true;
	if ((index % Map::MAP_WIDTH) == 0)
		return true;
	if ((index % Map::MAP_WIDTH) == Map::MAP_WIDTH - 1)
		return true;

	return false;
}

void Map::startCrumbling(int index)
{
	this->changeTileState(index, Map::CRUMBLING_TILE[0]);
	areTilesCrumbling = true;
	crumbleCounter = std::make_unique<Animation>();
	crumbleCounter->startMeasureTime(30);
}


void Map::updateCrumbling()
{
	if (areTilesCrumbling && crumbleCounter->checkIfTimePassed())
	{
		if (0 != std::ranges::count_if(mapping, [](int n) {return n >= 3; }))
		{
			std::vector<int> tilesToChange;
			for (int q{ 1 }; q < MAP_HEIGHT - 1; q++)
			{
				for (int w{ 1 }; w < MAP_WIDTH - 1; w++)
				{
					size_t i = w + q * MAP_WIDTH;
					if (mapping[i] >= CRUMBLING_TILE[0] && mapping[i] <= CRUMBLING_TILE[3]) //tile is crumbling, increment and spread
					{
						changeTileState(i, mapping[i] + 1);
						if (mapping[i - 1] == Map::TAIL_TILE)
							tilesToChange.push_back(i - 1);
						if (mapping[i + 1] == Map::TAIL_TILE)
							tilesToChange.push_back(i + 1);
						if (mapping[i + Map::MAP_WIDTH] == Map::TAIL_TILE)
							tilesToChange.push_back(i + Map::MAP_WIDTH);
						if (mapping[i - Map::MAP_WIDTH] == Map::TAIL_TILE)
							tilesToChange.push_back(i - Map::MAP_WIDTH);
					}
					if (mapping[i] > CRUMBLING_TILE[3]) //tile has crumbled, make it empty tile
						changeTileState(i, Map::EMPTY_TILE);
				}
			}

			for (int i{ 0 }; i < tilesToChange.size(); i++)
				changeTileState(tilesToChange[i], CRUMBLING_TILE[0]);
			crumbleCounter->startMeasureTime(30);
		}
		else //stop crumbling if no tail
		{
			areTilesCrumbling = false;
			crumbleCounter.release();
		}
	}
}
