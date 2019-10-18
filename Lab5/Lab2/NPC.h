#ifndef NPC_HPP
#define NPC_HPP
#include <SFML/Graphics.hpp>
#include "Kinematic.h"
#include <cstdlib>    
#include <ctime>   
enum Type 
{ 
	wander, 
	seek, 
	arrive,
	flee,
	pursue,
	form
};
class NPC
{
public:
	NPC();
	void kinematicWander(float t_deltaTime);
	void kinematicSeek(float t_deltaTime, sf::Vector2f& t_playerPos);
	void kinematicFlee(float t_deltaTime, sf::Vector2f& t_playerPos);
	void kinematicArrive(float t_deltaTime, sf::Vector2f& t_playerPos);
	void dynamicPursue(float t_deltaTime, sf::Vector2f& t_playerPos, sf::Vector2f& t_playerVelo);
	void closestApproach();

	void update(float t_deltaTime, sf::Vector2f& t_playerPos, sf::Vector2f& t_playerVelo);
	void render(sf::RenderWindow& t_window);
	void setupBehaviourAndSprite(Type t_type);
	sf::Vector2f getPosition() { return m_myPosition; }
private:
	const short MAX_TIME_PRED = 1000; // ms
	Type m_behaviourType;
	void m_generateTarget();
	void m_move();
	sf::Texture m_spriteTexture;
	sf::Sprite m_sprite;
	sf::Vector2f m_velocity;
	sf::Vector2f m_myPosition;
	sf::Vector2f m_targetPosition;
	float m_orientation;
	float m_rotation;
};
#endif
