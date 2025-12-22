#ifndef TEXT_BOX
#define TEXT_BOX

#include <vector>
#include <string>
#include <memory>
#include <optional>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "FileManager.h"

/// <summary>
/// Implements a text box graphical element. It can be displayed on the screed and configured acording to one's needs
/// </summary>
class TextBox
{
	std::optional<sf::Text> text;
	std::optional<sf::Text> subtext;
	
	std::vector<std::unique_ptr<Button>> buttons;

	bool useFrame{ true };
	bool fullFrame{ false };
	sf::RectangleShape frame;

	bool isActive = true;

	/// <summary>
	/// Method sets up all needed parameters for SFML text.
	/// </summary>
	/// <param name="text">Reference to configured text</param>
	/// <param name="s">Words that are to be displayed</param>
	/// <param name="textSize">Font size</param>
	void setUpText(sf::Text& text, std::string s, float textSize);

	/// <summary>
	/// Method sets up all needed parameters for SFML drawable rectangle.
	/// </summary>
	/// <param name="_x">Upper left corner x coordinate of the frame</param>
	/// <param name="_y">Upper left corner y coordinate of the frame</param>
	/// <param name="_w">Frame width</param>
	/// <param name="_h">Frame height</param>
	void setUpFrame(int _x, int _y, int _w, int _h);

public:

	/// <summary>
	/// Constructor for default text box
	/// </summary>
	/// <param name="_x">Upper left corner x coordinate</param>
	/// <param name="_y">Upper left corner y coordinate</param>
	/// <param name="_w">box width</param>
	/// <param name="_h">box height</param>
	/// <param name="_text"text displayed in box></param>
	/// <param name="_subtext">extra text displayed bellow main text in the box (by default none)</param>
	TextBox(int _x, int _y, int _w, int _h, std::string _text, std::string _subtext);
	
	/// <summary>
	/// Alternative constructor, allows for change of text on the button
	/// </summary>
	/// <param name="_x">Upper left corner x coordinate</param>
	/// <param name="_y">Upper left corner y coordinate</param>
	/// <param name="_w">box width</param>
	/// <param name="_h">box height</param>
	/// <param name="_text"text displayed in box></param>
	/// <param name="_subtext">extra text displayed bellow main text in the box (by default none)</param>
	/// <param name="buttonLabel">Text on button(by default "Back")</param>
	TextBox(int _x, int _y, int _w, int _h, std::string _text, std::string _subtext, std::string buttonLabel);
	
	/// <summary>
	/// Alternative constructor, creates a text box with extra button
	/// </summary>
	/// <param name="_x">Upper left corner x coordinate</param>
	/// <param name="_y">Upper left corner y coordinate</param>
	/// <param name="_w">box width</param>
	/// <param name="_h">box height</param>
	/// <param name="_text"text displayed in box></param>
	/// <param name="_subtext">extra text displayed bellow main text in the box (by default none)</param>
	/// <param name="buttonLabel1">Text on first button</param>
	/// <param name="buttonLabel2">Text on extra button</param>
	TextBox(int _x, int _y, int _w, int _h, std::string _text, std::string _subtext, std::string buttonLabel1, std::string buttonLabel2);

	/// <summary>
	/// Method turns on and off visibility of rectangular frame displayed around the box
	/// </summary>
	/// <param name="on_off">True to turn the frame on, false otherwise</param>
	void turnFrame(bool on_off);

	/// <summary>
	/// Method turns on and off visibility background color of the box, if left invisible box is transparent
	/// </summary>
	/// <param name="on_off">True to fill the box with color, false otherwise</param>
	void fillFrame(bool on_off);

	/// <summary>
	/// Method draws the box together with buttons and text in the window
	/// </summary>
	/// <param name="win">Reference to window on which the box will be drawn</param>
	void displayTextBox(sf::RenderWindow& win);

	/// <summary>
	/// Method check if any of active buttons have been presed
	/// </summary>
	/// <param name="win">Reference to window on which button is being displayed</param>
	/// <returns>Returns a pair, boolean value - true if any button was pressed, int - index of the pressed button</returns>
	std::pair<bool, int> waitForButton(sf::RenderWindow& win);
};


#endif // !TEXT_BOX
