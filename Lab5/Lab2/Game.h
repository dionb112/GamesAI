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
	const std::string INDIVIDUAL = "individual";
	const std::string FORMATION = "formation";
	std::string m_behaviour;
	bool m_turningRight;
	bool m_turningLeft;
	const sf::Uint8 FORTY_TWO = 4.2f;
	Player m_player;
	std::vector<sf::Vector2f *> m_positionSlots;
	std::vector<NPC *> m_NPCs;
	std::vector<sf::Text *> m_NPCTexts; // text used for message on screen
	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	bool m_exitGame; // control exiting game
	void processEvents();
	void processKeyPressed(sf::Event t_event);
	void processKeyReleased(sf::Event t_event);
	void update(float t_deltaTime);
	void render();
	void setupFontAndText();
	void setNPCData();
	void setupNPCs();
};
#endif // !GAME_HPP
