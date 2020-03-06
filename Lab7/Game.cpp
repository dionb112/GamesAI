/// <summary>
/// @author Dion Buckley
/// @date March 2020
/// fuzzy logic implementation
/// </summary>

#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ 1280U, 720U, 32U }, "Lab 7" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture

	// first number (8) gives 5 enemeny unit sized force 
		// TODO: this number should be random
	m_tiny = FuzzyLogic::fuzzyTriangle(8, -10, 0, 10); 
	m_small = FuzzyLogic::fuzzyTrapezoid(8, 2.5, 10, 15, 20); 
	m_moderate = FuzzyLogic::fuzzyTrapezoid(8, 15, 20, 25, 30);
	m_large = FuzzyLogic::fuzzyGrade(8, 25, 30);

	// enemy force at range of 25 units
		// TODO: this number should also be random
	m_close = FuzzyLogic::fuzzyTriangle(25, -30, 0, 30);
	m_medium = FuzzyLogic::fuzzyTrapezoid(25, 10, 30, 50, 70);
	m_far = FuzzyLogic::fuzzyGrade(25, 50, 70);

	// Final threat assessment
	m_low = FuzzyLogic::fuzzyOr(FuzzyLogic::fuzzyAnd(m_medium, m_tiny), FuzzyLogic::fuzzyAnd(m_medium, m_small));
	m_medium = FuzzyLogic::fuzzyAnd(m_close, m_tiny);
	m_high = FuzzyLogic::fuzzyAnd(m_close, FuzzyLogic::fuzzyNot(m_medium));

	// test with values from slides 
		// output matches expected values, good
	std::cout << m_low << std::endl;
	std::cout << m_medium << std::endl;
	std::cout << m_high << std::endl;
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


void Game::update(sf::Time t_deltaTime) // dt is time interval per frame
{
	if (m_exitGame)
	{
		m_window.close();
	}
}


void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_window.draw(m_welcomeMessage);
	m_window.draw(m_logoSprite);
	m_window.display();
}


void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("AI force fight");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(90.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(42U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}


void Game::setupSprite()
{
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\fuzzy.png"))
	{
		std::cout << "problem loading logo" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture);
}
