#ifndef NPC_HPP
#define NPC_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Kinematic.h"
#include <cstdlib>    
#include <ctime>   
enum Type 
{ 
	wander, 
	seek, 
	flee
};
class NPC
{
public:
	NPC();
	void kinematicFlee();
	void kinematicSeek();
	void kinematicArrive();
	void kinematicWanderer();
	void update(float t_deltaTime);
	void render(sf::RenderWindow& t_window);
	void setupBehaviourAndSprite(Type t_type);
private:
	Type m_behaviourType;
	void generateTarget();
	void screenWrap();
	void move();
	const float MAX_VELOCITY = 0.5f;
	const float MIN_VELOCITY = 0.05f;
	const float ROTATION_CHANGE = 6.0f;
	const unsigned int SCR_W = 1920;
	const unsigned int SCR_H = 1080;
	sf::Texture m_spriteTexture;
	sf::Sprite m_sprite;
	sf::Vector2f m_velocity;
	sf::Vector2f m_myPosition;
	sf::Vector2f m_targetPosition;
	float m_orientation;
	float m_rotation;
};
#endif
