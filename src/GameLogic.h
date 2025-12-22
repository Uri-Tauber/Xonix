#ifndef LOGIC
#define LOGIC

#include "Enemy.h"
#include "DefaultEnemy.h"
#include "DestroyerEnemy.h"
#include "HunterEnemy.h"

#include "Map.h"
#include "Player.h"

#include "KeyboardImput.h"
#include "GWindow.h"
#include "FileManager.h"

#include <memory>
#include <thread>
#include <vector>


class GameLogic
{
	bool gameOver = false;
	bool isMenuActive = true;
	bool isPauseActive = false;
	bool isDefeatBoxActive = false;
	bool isGameCompleted = false;

	int hitPoints; //+1 after finished level, -1 if any game over condition met
	int nextLevelIndex = 2;
	int currentLevelIndex = 1;
	static const int maxLevels = 20;

	std::vector<std::string> levels;
	std::vector<int> levelInfo;
	std::vector<int> nextLevelInfo;

	std::shared_ptr<Map> map;
	std::shared_ptr<Player> player;
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<std::shared_ptr<Enemy>> nextLevelEnemies;

	KeyboardImput kI;
	GWindow winG;

	std::thread nextLevelLoader;

public:

	/// <summary>
	/// Constructor, invokes game loop
	/// </summary>
	GameLogic() { start(); };

	/// <summary>
	/// Method initialises game menu, then invokes set up methods and run method
	/// </summary>
	void start();

	/// <summary>
	/// Basically a game loop, invokes event handling methods and drawing methods every frame
	/// </summary>
	void run();

	/// <summary>
	/// Method then set up basic game components 
	/// </summary>
	/// <param name="doLoadGame">If true, app will try to load game form the file</param>
	/// <returns>True if initialization succeeded</returns>
	bool initializeGame(bool doLoadGame);

	/// <summary>
	/// Sets up new enemies, resets mapa and player position
	/// </summary>
	void setUpNextLevel();
	
	/// <summary>
	/// Checks area covered in Wall tiles and compares it to percentage needed to completion
	/// </summary>
	/// <returns>Returns true if conditions have been met</returns>
	bool checkLevelCompletion();

	/// <summary>
	/// Gets level information from the string and converts it to integers
	/// </summary>
	/// <param name="index">Index of level analysed</param>
	void getLevelInformation(int index);

	/// <summary>
	/// Asks for level information and initialize all enemies	/// </summary>
	/// <param name="lvlIndex">Index of prepared level</param>
	void prepareNextLevel(int lvlIndex);

	/// <summary>
	/// Handles operations related to entities movement and tile filling
	/// </summary>
	void calculateLogic();

	/// <summary>
	/// Check if conditons to decrement players hit points have been met
	/// Checks if enemies touched the tail and activates tail crumbling
	/// </summary>
	/// <returns>Returns true if player hit its tail / touched enemy </returns>
	bool checkLivesLossConditions();

	/// <summary>
	/// Takes care of all events possible in game loop (game logic and interface)
	/// </summary>
	void handleEvents();

	/// <summary>
	/// Calculates all events related to game logic specifically
	/// </summary>
	void handleGameConditions();

	/// <summary>
	/// Handles operations related to level completion and initialization of next level
	/// </summary>
	void nextLevelProc();

	/// <summary>
	/// Method inveked every time player looses a hp. Resets its position to starting point
	/// and removes tail
	/// </summary>
	void deathProc();

	/// <summary>
	/// Draws all entities active on the window
	/// </summary>
	void drawEntities();

	/// <summary>
	/// Draws all panels ("static objects") in the window
	/// </summary>
	void drawPanels();

	/// <summary>
	/// Saves via FileManager current game state
	/// </summary>
	void saveGame();

	/// <summary>
	/// Loads information from file about last saved game state
	/// </summary>
	void loadGame();

	/// <summary>
	/// Fills all empty tiles touching enemy entities with mask value
	/// </summary>
	/// <param name="XY">Index of tile bellow enemy / last tile if in recurrency occures</param>
	void drop(int XY); 

	/// <summary>
	/// Invokes drop method for every enemy and tells Map object to fill unmasked tiles
	/// </summary>
	/// <param name="positions">Positions of all enemies</param>
	void conquer(std::vector<int> positions);

	~GameLogic();
};

#endif //LOGIC