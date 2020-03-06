#ifndef GAME_HPP // include guards
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "FuzzyLogic.h"

class Game
{
public:
	Game();
	~Game();
	void run();

private:
	// threat size
	float m_tiny;
	float m_small;
	float m_moderate;
	float m_large;
	// threat distance
	float m_close;
	float m_medium; // and assessment
	float m_far;
	// threat assesment
	float m_low;
	float m_high;

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_text; // text used for message on screen
	sf::Texture m_texture; // texture used for sfml logo
	sf::Sprite m_sprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game
};

#endif // !GAME_HPP