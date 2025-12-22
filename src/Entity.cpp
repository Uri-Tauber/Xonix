#include "Entity.h"


void Entity::loadTextures(int type)
{
	body.setTexture(FileManager::get_tx(type));
	body.setTextureRect(sf::IntRect({0, 0}, {ENTITY_RADIUS * 2, ENTITY_RADIUS * 2}));
}

Entity::Entity(int s) : speed(s), body(FileManager::get_tx(FileManager::PLAYER_TX)) // Placeholder
{
	animation = std::make_unique<Animation>();
}

void Entity::draw(sf::RenderWindow& win)
{
	if (animation->update())
		animation->applyToSprite(body);

	win.draw(body);
}

std::pair<int, int> Entity::getDside()
{
	int x = (int)body.getPosition().x;
	int y = (int)body.getPosition().y + ENTITY_RADIUS;
	return { x,y };
};
std::pair<int, int> Entity::getUside()
{
	int x = (int)body.getPosition().x;
	int y = (int)body.getPosition().y - ENTITY_RADIUS;
	return { x,y };
};
std::pair<int, int> Entity::getLside()
{
	int x = (int)body.getPosition().x - ENTITY_RADIUS;
	int y = (int)body.getPosition().y;
	return { x,y };
};
std::pair<int, int> Entity::getRside()
{
	int x = (int)body.getPosition().x + ENTITY_RADIUS;
	int y = (int)body.getPosition().y;
	return { x,y };
};

bool Entity::checkEntityCollisions(Entity& e)
{
	if ((this->getLside().first < e.getLside().first && this->getRside().first > e.getLside().first)
		|| (this->getLside().first < e.getRside().first && this->getRside().first > e.getRside().first)) //check X axis
		if ((this->getDside().second > e.getDside().second && this->getUside().second < e.getDside().second)
			|| (this->getDside().second > e.getUside().second && this->getUside().second < e.getUside().second)) //check Y axis			
				return true;

	return false;
}

int Entity::getIndexOfTile()
{
	int X = ((int)body.getPosition().x - (int)body.getPosition().x % Map::TILE_SIZE) / Map::TILE_SIZE;
	int Y = ((int)body.getPosition().y - (int)body.getPosition().y % Map::TILE_SIZE) / Map::TILE_SIZE;
	return (X + Y * Map::MAP_WIDTH);
}

std::pair<bool, int> Entity::checkTailCollisons(Map& map)
{
	std::pair<int, int> vert = { 0,0 };
	std::pair<int, int> horiz = { 0,0 };

	if (velocity.second > 0) //moves downwards
	{
		vert = getDside();
		vert.second += speed;
	}
	else if (velocity.second < 0) //moves upwards
	{
		vert = getUside();
		vert.second -= speed;
	}

	if (velocity.first > 0) //moves to the right
	{
		horiz = getRside();
		horiz.first += speed;
	}
	else if (velocity.first < 0) //moves to the left
	{
		horiz = getLside();
		horiz.first -= speed;
	}

	if (velocity.second != 0)
	{
		int X = (vert.first - vert.first % Map::TILE_SIZE) / Map::TILE_SIZE;
		int Y = (vert.second - vert.second % Map::TILE_SIZE) / Map::TILE_SIZE;
		int index = X + Y * Map::MAP_WIDTH;

		int tileType = map.getTileState(index);
		if (tileType == Map::TAIL_TILE)
			return std::make_pair(true, index);

	}
	if (velocity.first != 0)
	{
		int index = (horiz.first - horiz.first % Map::TILE_SIZE) / Map::TILE_SIZE
			+ (Map::MAP_WIDTH * ((horiz.second - horiz.second % Map::TILE_SIZE) / Map::TILE_SIZE));

		int tileType = map.getTileState(index);
		if (tileType == Map::TAIL_TILE)
			return std::make_pair(true, index);

	}
	return std::make_pair(false, -1);
}

