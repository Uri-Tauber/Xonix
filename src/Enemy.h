#ifndef ENEMY_DEFAULT
#define ENEMY_DEFAULT

#include <random>
#include <iostream>
#include "Entity.h"

/// <summary>
/// Parent class for specialized Enemies classes 
/// </summary>
class Enemy : public Entity
{
	int type;
protected:

	Enemy(int speed) : Entity(speed) {};


	/// <summary>
	/// Method changes velocity and direction of entity after certain conditions 
	/// </summary>
	/// <param name="param">Integer that specifies additional conditions</param>
	/// <returns>Returns boolean value, true if direction has been changed</returns>
	virtual bool changeDirection(int param) = 0;

	/// <summary>
	/// Method check if entity has collided with any tile on map considered as WALL type
	/// </summary>
	/// <param name="map">Takes active map reference as parameter</param>
	/// <returns>Return a value that indicates if collicion was horizontal (returned value = 2) or vertical (returned value = 1)</returns>
	int checkWallCollisons(Map& map);

	/// <summary>
	/// Method uses random number generator to give random number in range
	/// </summary>
	/// <param name="rangeFrom">Begining of the range (incuded)</param>
	/// <param name="rangeTo">End of the range (incuded)</param>
	/// <returns>Returns a random number</returns>
	int getRandomStartingPos(int rangeFrom, int rangeTo);

};

#endif // !ENEMY_DEFAULT
