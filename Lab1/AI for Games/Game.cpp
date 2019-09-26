/// <summary>
/// @author Dion Buckley
/// @date Sep 2019
///
/// </summary>
#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ SCR_W, SCR_H, 32U }, "SFML Game" },
	m_exitGame{false}, //when true game will exit
	m_velocity(0.1f, 0.0f)
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}

/// <summary>
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
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


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	else if (sf::Keyboard::Up == t_event.key.code)
	{
		if (m_velocity.x < 10)
		{
			m_velocity.x += 0.1f;
		}
	}
	else if (sf::Keyboard::Down == t_event.key.code)
	{
		if (m_velocity.x >= 0.1)
		{
			m_velocity.x -= 0.1f;
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	else 
	{
		m_sprite1.move(1 * m_velocity.x, 0);
		m_sprite2.move(-3, 0);
		if (m_sprite1.getPosition().x > SCR_W + m_sprite1.getOrigin().x / 2)
		{
			m_sprite1.setPosition(0 - m_sprite1.getOrigin().x / 3, m_sprite1.getPosition().y);
		}
		if (m_sprite2.getPosition().x < 0 - m_sprite2.getOrigin().x / 2)
		{
			m_sprite2.setPosition(SCR_W + m_sprite2.getOrigin().x / 3, m_sprite2.getPosition().y);
		}
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_welcomeMessage);
	m_window.draw(m_sprite1);
	m_window.draw(m_sprite2);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("Lab1");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_spriteTexture.loadFromFile("ASSETS\\IMAGES\\sprite.png"))
	{
		std::cout << "problem loading sprite" << std::endl;
	}
	m_sprite1.setTexture(m_spriteTexture);
	m_sprite2.setTexture(m_spriteTexture);
	m_sprite1.setPosition(300.0f,200.0f);
	m_sprite2.setPosition(550, 444);
	m_sprite1.setScale(-0.4, 0.4);
	m_sprite2.setScale(0.4, 0.4);
	m_sprite1.setOrigin(m_spriteTexture.getSize().x / 2, m_spriteTexture.getSize().y / 2);
	m_sprite2.setOrigin(m_spriteTexture.getSize().x / 2, m_spriteTexture.getSize().y / 2);
}
