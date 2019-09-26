#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Kinematic.h"
class Player
{
public:
	Player();
	void right();
	void left();
	void up();
	void down();
	void update(float t_deltaTime);
	void render(sf::RenderWindow & t_window);
	void setupSprite();
private:
	void direct();
	void screenWrap();
	void move(float t_deltaTime);
	const float MAX_VELOCITY = 0.5f;
	const float MIN_VELOCITY = 0.05f;
	const float ROTATION_CHANGE = 6.0f;
	const unsigned int SCR_W = 1920.0f;
	const unsigned int SCR_H = 1080.0f;
	sf::Texture m_spriteTexture;
	sf::Sprite m_sprite;
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
	float m_orientation;
	float m_rotation;
};
#endif
