#include "Enemy.h"

int Enemy::checkWallCollisons(Map& map) //0 for no coll, 1 for vert coll, 2 for horizon coll
{
	std::pair<int, int> vert = { 0,0 };
	std::pair<int, int> horiz = { 0,0 };

	int collisionDir = 0;

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
		if (tileType == Map::WALL_TILE)
			collisionDir = 1;
		if (tileType == Map::TAIL_TILE)
			collisionDir = 1;
	}

	if (velocity.first != 0)
	{
		int index = (horiz.first - horiz.first % Map::TILE_SIZE) / Map::TILE_SIZE
			+ (Map::MAP_WIDTH * ((horiz.second - horiz.second % Map::TILE_SIZE) / Map::TILE_SIZE));

		int tileType = map.getTileState(index);
		if (tileType == Map::WALL_TILE)
			collisionDir = 2;
		if (tileType == Map::TAIL_TILE)
			collisionDir = 2;
	}

	return collisionDir;
}

int Enemy::getRandomStartingPos(int rangeFrom, int rangeTo)
{
	std::random_device rand_dev;
	std::mt19937       generator(rand_dev());

	std::uniform_int_distribution<>  randoMachine(rangeFrom, rangeTo);

	return randoMachine(generator);
}