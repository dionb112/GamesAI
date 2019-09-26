/// <summary>
/// @author Dion Buckley
/// @date Sep 2019
///
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	void run();
private:
	const unsigned int SCR_W = 1920.0f;
	const unsigned int SCR_H = 1080.0f;

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_spriteTexture; 
	sf::Sprite m_sprite1; 
	sf::Sprite m_sprite2;
	sf::Vector2f m_velocity;
	bool m_exitGame; // control exiting game
	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void setupFontAndText();
	void setupSprite();
};
#endif // !GAME_HPP
