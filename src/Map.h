#ifndef MAP
#define MAP

#include <SFML/Graphics.hpp>
#include <array>
#include <ranges>
#include <memory>
#include <optional>
#include "FileManager.h"
#include "Animation.h"

/// <summary>
/// Class represents background and tile layer of the game
/// </summary>
class Map
{
	std::optional<sf::Sprite> backgroundSprite;
	
	std::unique_ptr<Animation> crumbleCounter;
	bool areTilesCrumbling = false;

	std::array<int, 1620> mapping;

	/// <summary>
	/// Loads and sets background image
	/// </summary>
	void createBackground();

public:
	constexpr static int MAP_WIDTH = 54; //in blocks
	constexpr static int MAP_HEIGHT = 30;//in blocks
	constexpr static int MAP_WIDTH_PIXELS = 1620; //in blocks
	constexpr static int MAP_HEIGHT_PIXELS = 900;//in blocks

	constexpr static int TILE_SIZE = 30; //in px

	constexpr static int WALL_TILE = 1;
	constexpr static int TAIL_TILE = 2;
	constexpr static int EMPTY_TILE = 0;
	constexpr static int OCCUPIED_TILE = -1;

	const std::array<int, 4> CRUMBLING_TILE = {3,4,5,6};

	/// <summary>
	/// Method draws all visible tiles
	/// </summary>
	/// <param name="win">Reference to the window on which elements will be drawn</param>
	void draw(sf::RenderWindow& win) const;

	Map();

	/// <param name="index">Index of refered tile</param>
	/// <returns>Returns state of the tile. Posible states are: -1,0,1,2,3,4,5,6</returns>
	int getTileState(int index);

	/// <summary>
	/// Removes tail tiles from the map and replaces them with empty ones 
	/// </summary>
	void clearTail();

	/// <summary>
	/// Fills empty tiles (state = 0) with wall tiles ( state = 1 )
	/// </summary>
	void fillEmptySpace();

	/// <summary>
	/// Changes state of refered tile
	/// </summary>
	/// <param name="index">Index of refered tile</param>
	/// <param name="newState">New state of the tile</param>
	void changeTileState(int index, int newState);

	/// <summary>
	/// Calculates how many percent of the total tiles Wall tiles are covering
	/// </summary>
	/// <returns>Retruns percentage</returns>
	double getProggres();

	/// <summary>
	/// Resets map tiles, sets them acordingly to the file content
	/// </summary>
	void resetMap();

	/// <summary>
	/// Check if given tile is a tile on the edge of the map
	/// </summary>
	/// <param name="index">Index of tile</param>
	/// <returns>True if tile is on the edge</returns>
	bool isTileInOuterRing(int index);

	/// <summary>
	/// Method starts chain reaction of transforming tail tiles to crumble tiles
	/// </summary>
	/// <param name="index">Index of first tile to be crumbled</param>
	void startCrumbling(int index);

	/// <summary>
	/// Method escalates crumbling effect on other tiles and updates status on tiles that are already crumbling
	/// </summary>
	void updateCrumbling();

};

#endif // !MAP
