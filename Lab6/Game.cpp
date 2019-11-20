#include "Game.h"
#include <iostream>
Game::Game() :
	m_window{ sf::VideoMode{ SCR_W / 2, SCR_H - 225 , 32U }, "Flow field"},
	m_exitGame{false},
	m_goal(0,0),
	m_cellSize(SCR_W / 100, SCR_W / 100),
	m_rightClickState(false),
	m_prevStart(-1,-1),
	m_prevGoal(-1,-1)
{
	m_window.setVerticalSyncEnabled(1);
	setupSprite(); // load texture
	for (int i = 0; i < COLUMNS; i++) {
		for (int j = 0; j < ROWS; j++) {
			m_grid[i][j].setSize(m_cellSize);
			m_grid[i][j].setFillColor(sf::Color(0, 0, 0, 0));
			m_grid[i][j].setOutlineColor(sf::Color::Blue);
			m_grid[i][j].setOutlineThickness(1.0f);
			m_grid[i][j].setPosition(i * m_cellSize.x + 5.0f, j * m_cellSize.y + 5.0f);
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
		if (sf::Event::MouseButtonPressed == newEvent.type) //user pressed a key
		{
			if (sf::Mouse::Left == newEvent.mouseButton.button)
			{
				leftClick(newEvent);
			}
			if (sf::Mouse::Right == newEvent.mouseButton.button)
			{
				rightClick(newEvent);
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
		}
	}
	m_window.display();
}
void Game::leftClick(sf::Event t_event)
{
	for (int i = 0; i < COLUMNS; i++) {
		for (int j = 0; j < ROWS; j++) {
			if (sqrt(pow((m_grid[i][j].getPosition().x + m_cellSize.x / 2) - t_event.mouseButton.x, 2) + pow((m_grid[i][j].getPosition().y + m_cellSize.y / 2) - t_event.mouseButton.y, 2)) < m_cellSize.x / 1.75) {
				m_grid[i][j].setFillColor(sf::Color(255, 255, 255, 255));
			}
		}
	}
}
void Game::rightClick(sf::Event t_event)
{
	for (int i = 0; i < COLUMNS; i++) {
		for (int j = 0; j < ROWS; j++) {
			if (sqrt(pow((m_grid[i][j].getPosition().x + m_cellSize.x / 2) - t_event.mouseButton.x, 2) + pow((m_grid[i][j].getPosition().y + m_cellSize.y / 2) - t_event.mouseButton.y, 2)) < m_cellSize.x / 1.75) {
				if (m_rightClickState == false) {
					m_grid[i][j].setFillColor(sf::Color::Green);
					m_rightClickState = true;
					if (m_prevStart != sf::Vector2i{ -1,-1 }) {
						m_grid[m_prevStart.x][m_prevStart.y].setFillColor(sf::Color(0, 0, 0, 0));
					}
					m_prevStart = sf::Vector2i{ i,j };
				}
				else if (m_rightClickState == true) {
					m_grid[i][j].setFillColor(sf::Color::Red);
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
