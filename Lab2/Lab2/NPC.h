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
	flee,
	pursue
};
static const float MAX_VELOCITY = 0.5f;
static const float MIN_VELOCITY = 0.05f;
static const float ROTATION_CHANGE = 6.0f;
class NPC
{
public:
	NPC();
	void kinematicWander(float t_deltaTime);
	void kinematicSeek(float t_deltaTime, sf::Vector2f& t_playerPos);
	void kinematicFlee(float t_deltaTime, sf::Vector2f& t_playerPos);
	void kinematicArrive();
	void dynamicPursue(float t_deltaTime, sf::Vector2f& t_playerPos, sf::Vector2f& t_playerVelo);
	void update(float t_deltaTime, sf::Vector2f& t_playerPos, sf::Vector2f& t_playerVelo);
	void render(sf::RenderWindow& t_window);
	void setupBehaviourAndSprite(Type t_type);
	sf::Vector2f getPosition() { return m_myPosition; }
private:
	Type m_behaviourType;
	void m_generateTarget();
	void m_screenWrap();
	void m_move();

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
