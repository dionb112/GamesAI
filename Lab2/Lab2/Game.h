/// <summary>
/// @author Dion Buckley
/// @date Sep 2019
///
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "NPC.h"

class Game
{
public:
	Game();
	void run();
private:
	const sf::Uint8 FORTY_TWO = 4.2f;
	Player m_player;
	std::vector<NPC *> m_NPCs;
	std::vector<sf::Text *> m_NPCTexts; // text used for message on screen
	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	bool m_exitGame; // control exiting game
	void processEvents();
	void processKeys(sf::Event t_event);
	void update(float t_deltaTime);
	void render();
	void setupFontAndText();
	void setupSprite();
	void setupNPCs();
};
#endif // !GAME_HPP
