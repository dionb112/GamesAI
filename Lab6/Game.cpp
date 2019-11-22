#include "Game.h"
#include <iostream>
Game::Game() :
	m_window{ sf::VideoMode{ SCR_W / 2, SCR_H - 225 , 32U }, "Flow field"},
	m_exitGame{false},
	m_goal(0,0),
	m_cellSize(SCR_W / 60, SCR_W / 60),
	m_rightClickState(false),
	m_prevStart(-1,-1),
	m_prevGoal(-1,-1),
	m_isLeftMouseHeld(false),
	m_isMiddleMouseHeld(false)
{
	g.init(COLUMNS * ROWS);
	m_window.setVerticalSyncEnabled(1);
	setupSprite(); // load texture
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	for (int i = 0; i < COLUMNS; i++) {
		for (int j = 0; j < ROWS; j++) {
			m_grid[i][j].setSize(m_cellSize);
			m_grid[i][j].setFillColor(sf::Color(0, 0, 0, 0));
			m_grid[i][j].setOutlineColor(sf::Color::Blue);
			m_grid[i][j].setOutlineThickness(1.0f);
			m_grid[i][j].setPosition(i * m_cellSize.x + 5.0f, j * m_cellSize.y + 5.0f);
			// m_graph[i][j] = i + j / 2;
			g.addEdge(0, i * j);
			m_numbers[i][j].setFont(m_ArialBlackfont);
			m_numbers[i][j].setString(std::to_string(i + j / 2));
			m_numbers[i][j].setStyle(sf::Text::Bold);
			m_numbers[i][j].setPosition(m_grid[i][j].getPosition());
			m_numbers[i][j].setCharacterSize(m_cellSize.x / 3);
			m_numbers[i][j].setOutlineColor(sf::Color::Red);
			m_numbers[i][j].setFillColor(sf::Color::Black);
			m_numbers[i][j].setOutlineThickness(1.0f);
		}
	}
}
Game::~Game()
{
}
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseButtonPressed == newEvent.type) //user pressed a mouse
		{
			if (sf::Mouse::Left == newEvent.mouseButton.button)
			{
				m_isLeftMouseHeld = true;
			}
			else if (sf::Mouse::Middle == newEvent.mouseButton.button)
			{
				m_isMiddleMouseHeld = true;
			}
			if (sf::Mouse::Right == newEvent.mouseButton.button)
			{
				rightClick(newEvent);
			}
		}
		else if (sf::Event::MouseButtonReleased == newEvent.type) //user released mouse
		{
			if (sf::Mouse::Left == newEvent.mouseButton.button)
			{
				m_isLeftMouseHeld = false;
			}
			else if (sf::Mouse::Middle == newEvent.mouseButton.button)
			{
				m_isMiddleMouseHeld = false;
			}
		}
	}
}
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	if (m_isLeftMouseHeld == true) {
		leftClick();
	}
	else if (m_isMiddleMouseHeld == true) {
		middleClick();
	}
	// if colour of tile is white -> not traversable
}
/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_window.draw(m_arrowSprite);
	for (int i = 0; i < COLUMNS; i++) {
		for (int j = 0; j < ROWS; j++) {
			m_window.draw(m_grid[i][j]);
			m_window.draw(m_numbers[i][j]);
		}
	}
	m_window.display();
}
void Game::leftClick()
{
	for (int i = 0; i < COLUMNS; i++) {
		for (int j = 0; j < ROWS; j++) {
			if (sqrt(pow((m_grid[i][j].getPosition().x + m_cellSize.x / 2) - sf::Mouse::getPosition(m_window).x, 2) + pow((m_grid[i][j].getPosition().y + m_cellSize.y / 2) - sf::Mouse::getPosition(m_window).y, 2)) < m_cellSize.x) {
				if (m_grid[i][j].getFillColor() == sf::Color(0, 0, 0, 0)) {
					m_grid[i][j].setFillColor(sf::Color(255, 255, 255, 255));
				}
			}
		}
	}
}
void Game::middleClick()
{
	for (int i = 0; i < COLUMNS; i++) {
		for (int j = 0; j < ROWS; j++) {
			if (sqrt(pow((m_grid[i][j].getPosition().x + m_cellSize.x / 2) - sf::Mouse::getPosition(m_window).x, 2) + pow((m_grid[i][j].getPosition().y + m_cellSize.y / 2) - sf::Mouse::getPosition(m_window).y, 2)) < m_cellSize.x * 1.25f ) {
				if (m_grid[i][j].getFillColor() == sf::Color(255, 255, 255, 255)) {
					m_grid[i][j].setFillColor(sf::Color(0, 0, 0, 0));
				}
			}
		}
	}
}
void Game::rightClick(sf::Event t_event)
{
	bool didBFS = false;
	list<int> myList;
	for (int i = 0; i < COLUMNS; i++) {
		for (int j = 0; j < ROWS; j++) {
			if (sqrt(pow((m_grid[i][j].getPosition().x + m_cellSize.x / 2) - t_event.mouseButton.x, 2) + pow((m_grid[i][j].getPosition().y + m_cellSize.y / 2) - t_event.mouseButton.y, 2)) < m_cellSize.x / 1.75) {
				if (m_rightClickState == false) {
					if (m_grid[i][j].getFillColor() != sf::Color::Red) {
						m_grid[i][j].setFillColor(sf::Color::Green);
					}
					m_rightClickState = true;
					if (m_prevStart != sf::Vector2i{ -1,-1 }) {
						m_grid[m_prevStart.x][m_prevStart.y].setFillColor(sf::Color(0, 0, 0, 0));
					}
					m_prevStart = sf::Vector2i{ i,j };
				}
				else if (m_rightClickState == true) {
					if (m_grid[i][j].getFillColor() != sf::Color::Green) {
						m_grid[i][j].setFillColor(sf::Color::Red);
						if (!didBFS) {
							myList = g.BFS(i * j);
							didBFS = true;
						}
						if (!myList.empty()) {
							m_numbers[i][j].setString(std::to_string(myList.front()));
							myList.pop_front();
						}
					}
					m_rightClickState = false;
					if (m_prevGoal != sf::Vector2i{ -1,-1 }) {
						m_grid[m_prevGoal.x][m_prevGoal.y].setFillColor(sf::Color(0, 0, 0, 0));
					}
					m_prevGoal = sf::Vector2i{ i,j };
				}
			}
		}
	}
}
void Game::setupSprite()
{
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\arrow.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading arrow" << std::endl;
	}
	m_arrowSprite.setTexture(m_logoTexture);
	m_arrowSprite.setPosition(10, 10);
}

int* Game::generateDijkstra(int graph[COLUMNS][ROWS], int src) /*Method to implement shortest path algorithm*/
{
	int dist[COLUMNS];
	bool Dset[COLUMNS];
	for (int i = 0; i < COLUMNS; i++)                    /*Initialize distance of all the vertex to INFINITY and Dset as false*/
	{
		dist[i] = INT_MAX;
		Dset[i] = false;
	}
	dist[src] = 0;                                   /*Initialize the distance of the source vertec to zero*/
	for (int c = 0; c < COLUMNS; c++)
	{
		int min = INT_MAX, u;                 /*initialize min with the maximum possible value as infinity does not exist */
		for (int v = 0; v < ROWS; v++)
		{
			if (Dset[v] == false && dist[v] <= min)
			{
				min = dist[v];
				u = v;
			}
		}              /*u is any vertex that is not yet included in Dset and has minimum distance*/
		Dset[u] = true;                              /*If the vertex with minimum distance found include it to Dset*/
		for (int v = 0; v < COLUMNS; v++)
			/*Update dist[v] if not in Dset and their is a path from src to v through u that has distance minimum than current value of dist[v]*/
		{
			if (!Dset[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
		}
	}
	std::cout << "Vertex\t\tDistance from source" << std::endl;
	for (int i = 0; i < COLUMNS; i++)                       /*will print the vertex with their distance from the source to the console */
	{
		char c = 65 + i;
		std::cout << c << "\t\t" << dist[i] << std::endl;
	}
	return dist;
}
