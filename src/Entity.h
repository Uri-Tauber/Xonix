#ifndef ENTITY
#define ENTITY

#include <memory>
#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "Map.h"
#include "FileManager.h"

class Entity
{
protected:
	std::pair<float, float> velocity;
	int speed;

	sf::Sprite body;

	std::unique_ptr<Animation> animation;
	Entity() = delete;

	/// <summary>
	/// Gets a desirable texture from FileManager resources 
	/// </summary>
	void loadTextures(int type);

public:

	constexpr static int ENTITY_RADIUS = 15;

	/// <summary>
	/// </summary>
	/// <param name="s">Speed of the entity</param>
	Entity(int s);

	virtual void move(Map& map) = 0;

	/// <summary>
	/// Draws entity sprite in the window
	/// </summary>
	/// <param name="win">Reference to window on which the sprite will be drawn</param>
	void draw(sf::RenderWindow& win);

	/// <summary>
	/// Calculates coordinates of bottom center of the entity (middle of the edge)
	/// </summary>
	/// <returns>Coordinates</returns>
	std::pair<int, int> getDside();
	/// <summary>
	/// Calculates coordinates of upper center of the entity (middle of the edge) 
	/// </summary>
	/// <returns>Coordinates</returns>
	std::pair<int, int> getUside();
	/// <summary>
	/// Calculates coordinates of left center of the entity (middle of the edge)
	/// </summary>
	/// <returns>Coordinates</returns>
	std::pair<int, int> getLside();
	/// <summary>
	/// Calculates coordinates of right center of the entity (middle of the edge)
	/// </summary>
	/// <returns>Coordinates</returns>
	std::pair<int, int> getRside();

	bool checkEntityCollisions(Entity& e);

	/// <summary>
	/// Checks if entity touched any Tail tile
	/// </summary>
	/// <param name="map">Reference to active map</param>
	std::pair<bool, int> checkTailCollisons(Map& map);

	/// <summary>
	/// Calculates an index of the tile bellow center of this entity
	/// </summary>
	/// <returns>Returns an index</returns>
	int getIndexOfTile();
};
#endif // !ENTITY
