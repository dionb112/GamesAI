#include "NPC.h"
NPC::NPC() :
	m_velocity{ -MAX_VELOCITY, 0.0f },
	m_position{ SCR_W / 2, SCR_H / 2 },
	m_orientation{ 0.0f },
	m_rotation{ 0.0f }
{
}

void NPC::update(float t_deltaTime)
{
	move();
	screenWrap();
}
void NPC::kinematicWanderer()
{

}
void NPC::screenWrap()
{
	if (m_position.x < 0)
	{
		m_position = sf::Vector2f(SCR_W, m_position.y);
	}
	if (m_position.x > SCR_W)
	{
		m_position = sf::Vector2f(0, m_position.y);
	}
	if (m_position.y < 0)
	{
		m_position = sf::Vector2f(m_position.y, SCR_H);
	}
	if (m_position.y > SCR_H)
	{
		m_position = sf::Vector2f(m_position.y, 0);
	}
}
void NPC::move()
{
	m_position += m_velocity;
	m_sprite.setPosition(m_position);
}
void NPC::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_sprite);
}
void NPC::setupSprite()
{
	if (!m_spriteTexture.loadFromFile("ASSETS\\IMAGES\\NPC.png"))
	{
		std::cout << "problem loading sprite" << std::endl;
	}
	m_sprite.setTexture(m_spriteTexture);
	m_sprite.setOrigin(m_spriteTexture.getSize().x / 2, m_spriteTexture.getSize().y / 2);
}
