#include "Game.h"
#include <iostream>
Game::Game() :
	m_window{ sf::VideoMode{ SCR_W - 50, SCR_H - 100, 32U }, "Flow field"},
	m_exitGame{false} //when true game will exit
{
	m_window.setVerticalSyncEnabled(1);
	setupSprite(); // load texture
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
	sf::Vector2f cellSize(SCR_W / 51, SCR_H / 52);

	for (int i = 0; i < COLUMNS; i++) {
		for (int j = 0; j < ROWS; j++) {
			m_grid[i][j].setSize(cellSize);
			m_grid[i][j].setFillColor(sf::Color(0,0,0,0));
			m_grid[i][j].setOutlineColor(sf::Color::Blue);
			m_grid[i][j].setOutlineThickness(5.0f);
			m_grid[i][j].setPosition(i * cellSize.x + 5.0f, j * cellSize.y + 5.0f);
		}
	}
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