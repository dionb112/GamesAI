/// <summary>
/// author Dion Buckley 
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
static const unsigned int SCR_W = sf::VideoMode::getDesktopMode().width;
static const unsigned int SCR_H = sf::VideoMode::getDesktopMode().height;
class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:
	const static int COLUMNS = 50;
	const static int ROWS = 50;
	sf::RectangleShape m_grid[COLUMNS][ROWS];
	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_arrowSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP
