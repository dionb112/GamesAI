/// <summary>
/// @author Dion Buckley
/// @date Sep 2019
/// </summary>
#include "Game.h"
Game::Game() :
	m_window{ sf::VideoMode{ SCR_W, SCR_H, 32U }, "SFML Game", sf::Style::Fullscreen },
	m_exitGame{false} 
{
	m_window.setVerticalSyncEnabled(1);
	setupNPCs(); 
	setupFontAndText(); 
	setupSprite(); 
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
			update(timePerFrame.asMilliseconds()); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// </summary>
void Game::processEvents() {
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
void Game::processKeys(sf::Event t_event) {
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::Right == t_event.key.code)
	{
		m_player.right();
	}
	else if (sf::Keyboard::Left == t_event.key.code)
	{
		m_player.left();
	}
	if (sf::Keyboard::Up == t_event.key.code)
	{
		m_player.up();
	}
	else if (sf::Keyboard::Down == t_event.key.code)
	{
		m_player.down();
	}
}
/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(float t_deltaTime) {
	if (m_exitGame) {
		m_window.close();
	} else {
		m_player.update(t_deltaTime);
		for (int i = 0; i < m_NPCs.size(); i++) {
			m_NPCs[i]->update(t_deltaTime, m_player.getPosition(), m_player.getVelocity());
			m_NPCTexts[i]->setPosition(m_NPCs[i]->getPosition().x + 75, m_NPCs[i]->getPosition().y);
		}
	}
}
/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render() {
	m_window.clear(sf::Color{ FORTY_TWO, FORTY_TWO, FORTY_TWO });
	for (sf::Text* text : m_NPCTexts) {
		m_window.draw(*text);
	}
	m_player.render(m_window);
	for (NPC* npc : m_NPCs) {
		npc->render(m_window);
	}
	m_window.display();
}
/// /// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite() {
	m_player.setupSprite();
	m_NPCs[0]->setupBehaviourAndSprite(Type::wander);
	m_NPCs[1]->setupBehaviourAndSprite(Type::seek);
	m_NPCs[2]->setupBehaviourAndSprite(Type::flee);
	m_NPCs[3]->setupBehaviourAndSprite(Type::pursue);
}
void Game::setupNPCs()
{
	m_NPCs.reserve(4);
	m_NPCTexts.reserve(m_NPCs.capacity());
	for (int i = 0; i < m_NPCs.capacity(); i++) {
		m_NPCs.push_back(new NPC());
		m_NPCTexts.push_back(new sf::Text());
	}
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
	for (sf::Text* text : m_NPCTexts) {
		text->setFont(m_ArialBlackfont);
		text->setStyle(sf::Text::Italic);
		text->setCharacterSize(42U);
		text->setOutlineColor(sf::Color::Red);
		text->setFillColor(sf::Color::Black);
		text->setOutlineThickness(3.0f);
	}
	m_NPCTexts[0]->setString("Wander");
	m_NPCTexts[1]->setString("Seek");
	m_NPCTexts[2]->setString("Flee");
	m_NPCTexts[3]->setString("Pursue");
}
