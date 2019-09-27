#include "NPC.h"

NPC::NPC() :
	m_velocity{ -MAX_VELOCITY, 0.0f },
	m_myPosition{ SCR_W / 2, SCR_H / 2 },
	m_orientation{ 0.0f },
	m_rotation{ 0.0f },
	m_targetPosition{ 0.0f, 0.0f }
{
	srand(time(NULL)); // initialize 'random' seed
	generateTarget();
}

void NPC::kinematicFlee()
{
}

void NPC::update(float t_deltaTime)
{
	switch (m_behaviourType)
	{
	case wander:
		kinematicWanderer();
		break;
	case seek:
		kinematicSeek();
		break;
	case flee:
		kinematicFlee();
		break;
	default:
		break;
	}
	move();
	screenWrap();
}
void NPC::move()
{
	m_myPosition += m_velocity;
	m_sprite.setRotation(m_orientation);
	m_sprite.setPosition(m_myPosition);
}
void NPC::screenWrap()
{
	if (m_myPosition.x < 0)
	{
		m_myPosition = sf::Vector2f(SCR_W, m_myPosition.y);
	}
	if (m_myPosition.x > SCR_W)
	{
		m_myPosition = sf::Vector2f(0, m_myPosition.y);
	}
	if (m_myPosition.y < 0)
	{
		m_myPosition = sf::Vector2f(m_myPosition.y, SCR_H);
	}
	if (m_myPosition.y > SCR_H)
	{
		m_myPosition = sf::Vector2f(m_myPosition.y, 0);
	}
}

void NPC::generateTarget()
{
	float x = rand() % 1920;
	float y = rand() % 1080;
	m_targetPosition = sf::Vector2f{ x, y };
}
void NPC::kinematicSeek()
{
}
void NPC::kinematicArrive()
{
}
void NPC::kinematicWanderer()
{
	if (m_myPosition == m_targetPosition) // consider doing this sooner if taking too long
	{
		generateTarget();
	}
	m_velocity = m_targetPosition - m_myPosition;
	m_velocity = m_velocity / Kinematic::vectorLength(m_velocity);
	m_orientation = Kinematic::getNewOrientation(m_orientation, m_velocity, m_myPosition);
	m_orientation = m_orientation + ROTATION_CHANGE * ((rand() % 2) - 1); // rand 0 to 2 minus 1 gives -1 to 1 
	m_velocity = sf::Vector2f{ -sinf(m_orientation), cosf(m_orientation) } * MAX_VELOCITY;
}

void NPC::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_sprite);
}
void NPC::setupBehaviourAndSprite(Type t_type)
{	
	m_behaviourType = t_type
		;
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
