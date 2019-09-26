#ifndef NPC_HPP
#define NPC_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Kinematic.h"
class NPC
{
public:
	NPC();

	void update(float t_deltaTime);
	void render(sf::RenderWindow& t_window);
	void setupSprite();
private:
	void kinematicWanderer();
	void screenWrap();
	void move();
	const float MAX_VELOCITY = 7.0f;
	const float MIN_VELOCITY = 0.1f;
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
