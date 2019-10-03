#include "NPC.h"
NPC::NPC() :
	m_velocity{ -MAX_VELOCITY, 0.0f },
	m_myPosition{ SCR_W / 2, SCR_H / 2 },
	m_orientation{ 0.0f },
	m_rotation{ 0.0f },
	m_targetPosition{ 0.0f, 0.0f } {
	srand(time(NULL));			// initialize 'random' seed
	m_generateTarget();
}
void NPC::kinematicFlee(float t_deltaTime, sf::Vector2f& t_playerPos) {
	m_targetPosition = t_playerPos;
	m_velocity = m_myPosition - m_targetPosition;
	m_velocity = m_velocity / Kinematic::vectorLength(m_velocity) * (t_deltaTime / 4);
	m_velocity *= MAX_VELOCITY;
	m_orientation = Kinematic::getNewOrientation(m_orientation, m_velocity);
}
void NPC::update(float t_deltaTime, sf::Vector2f& t_playerPos) {
	switch (m_behaviourType)
	{
	case wander:
		kinematicWanderer(t_deltaTime / 4.2f);
		break;
	case seek:
		kinematicSeek(t_deltaTime / 4.2f, t_playerPos);
		break;
	case flee:
		kinematicFlee(t_deltaTime / 4.2f, t_playerPos);
		break;
	default:
		break;
	}
	m_move();
	m_screenWrap();
}
void NPC::m_move()
{
	m_myPosition += m_velocity;
	m_sprite.setRotation(m_orientation);
	m_sprite.setPosition(m_myPosition);
}
void NPC::m_screenWrap() {
	if (m_myPosition.x < 0)
	{
		m_generateTarget();
	}
	if (m_myPosition.x > SCR_W)
	{
		m_generateTarget();
	}
	if (m_myPosition.y < 0)
	{
		m_generateTarget();
	}
	if (m_myPosition.y > SCR_H)
	{
		m_generateTarget();
	}
}
void NPC::kinematicSeek(float t_deltaTime, sf::Vector2f& t_playerPos) {
	m_targetPosition = t_playerPos;
	m_velocity = m_targetPosition - m_myPosition;
	m_velocity = m_velocity / Kinematic::vectorLength(m_velocity) * t_deltaTime;
	m_velocity *= MAX_VELOCITY;
	m_orientation = Kinematic::getNewOrientation(m_orientation, m_velocity);
}
void NPC::kinematicArrive() {

}
void NPC::m_generateTarget() {
	float x = rand() % 2000;
	float y = rand() % 1200;
	m_targetPosition = sf::Vector2f{ x, y };
}
void NPC::kinematicWanderer(float t_deltaTime) {
	if (m_targetPosition.x - m_myPosition.x < 50 && m_targetPosition.y - m_myPosition.y < 11.11f)
	{
		m_generateTarget();
	}
	m_orientation = Kinematic::getNewOrientation(m_orientation, m_velocity);
	m_orientation = m_orientation + ROTATION_CHANGE * ((rand() % 2) - 1); // rand 0 to 2 minus 1 gives -1 to 1 
	m_velocity = sf::Vector2f{ -sinf(m_orientation), cosf(m_orientation) } * MAX_VELOCITY ;
	m_velocity = m_targetPosition - m_myPosition;
	m_velocity = m_velocity / Kinematic::vectorLength(m_velocity) * t_deltaTime;
}
void NPC::render(sf::RenderWindow& t_window) {
	t_window.draw(m_sprite);
}
/// <summary>
/// 
/// </summary>
/// <param name="t_type"></param>
void NPC::setupBehaviourAndSprite(Type t_type) {	
	m_behaviourType = t_type;
	switch (m_behaviourType)
	{
	case wander:
		if (!m_spriteTexture.loadFromFile("ASSETS\\IMAGES\\wanderer.png"))
		{
			std::cout << "problem loading wanderer" << std::endl;
		}		
		break;
	case seek:
		if (!m_spriteTexture.loadFromFile("ASSETS\\IMAGES\\seeker.png"))
		{
			std::cout << "problem loading seeker" << std::endl;
		}
		break;
	case flee:
		if (!m_spriteTexture.loadFromFile("ASSETS\\IMAGES\\scaredyCat.png"))
		{
			std::cout << "problem loading scaredy cat" << std::endl;
		}
		break;
	default:
		break;
	}
	m_sprite.setTexture(m_spriteTexture);
	m_sprite.setOrigin(m_spriteTexture.getSize().x / 2, m_spriteTexture.getSize().y / 2);
}
