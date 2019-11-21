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
	sf::Font m_ArialBlackfont; 
	bool m_isLeftMouseHeld;
	bool m_isMiddleMouseHeld;
	sf::Vector2i m_prevStart;
	sf::Vector2i m_prevGoal;
	bool m_rightClickState;
	sf::Vector2f m_cellSize;
	sf::Vector2f m_goal;
	const static int COLUMNS = 25;
	const static int ROWS = 25;
	int m_graph[COLUMNS][ROWS];
	sf::RectangleShape m_grid[COLUMNS][ROWS];
	sf::Text m_numbers[COLUMNS][ROWS];
	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void leftClick();
	void middleClick();
	void rightClick(sf::Event t_event);
	void setupSprite();
	void generateDijkstra(int t_graph[COLUMNS][ROWS], int src);

	sf::RenderWindow m_window; // main SFML window
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_arrowSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

