#include "Player.h"
Player::Player() : 
	m_velocity{ 0.0f, 0.0f },
	m_position{ SCR_W / 4, SCR_H / 4 },
	m_orientation{ 0.0f },
	m_rotation{ 0.0f }
{
}
void Player::right()
{
	m_rotation += ROTATION_CHANGE;
	direct();
}
void Player::left()
{
	m_rotation -= ROTATION_CHANGE;
	direct();
}
void Player::direct()
{
	m_velocity = Kinematic::vectorLength(m_velocity) * sf::Vector2f{ cos(Kinematic::toDegrees(m_rotation)), sin(Kinematic::toDegrees(m_rotation)) };
	/*m_orientation = Kinematic::getNewOrientation(m_orientation, m_velocity, m_position);
	if (t_isMinus)
	{
		m_velocity += sf::Vector2f{ -sin(m_orientation), cos(m_orientation) };
	}
	else
	{
		m_velocity += sf::Vector2f{ sin(m_orientation), cos(m_orientation) };
	}*/
}
void Player::up()
{
	if (Kinematic::vectorLength(m_velocity) == 0)
	{
		m_velocity += sf::Vector2f{ cos(m_rotation * PI / 180), sin(m_rotation * PI / 180) };
	}
	else
	{
		m_velocity += m_velocity / Kinematic::vectorLength(m_velocity);
	}
}
void Player::down()
{
	m_velocity *= 0.88f;
	if (Kinematic::vectorLength(m_velocity) < 0.1f)
	{
		m_velocity = sf::Vector2f{ 0.0f, 0.0f };
	}
}
void Player::update(float t_deltaTime)
{
	if (m_velocity.x > MAX_VELOCITY)
	{
		m_velocity.x = MAX_VELOCITY;
	}
	else if (m_velocity.x < -MAX_VELOCITY)
	{
		m_velocity.x = -MAX_VELOCITY;
	}
	if (m_velocity.y < -MAX_VELOCITY)
	{
		m_velocity.y = -MAX_VELOCITY;
	}
	else if (m_velocity.y > MAX_VELOCITY)
	{
		m_velocity.y = MAX_VELOCITY;
	}
	move(t_deltaTime);
	screenWrap();
}
void Player::screenWrap()
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
void Player::move(float t_deltaTime)
{
	m_position = m_position + m_velocity * t_deltaTime;
	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_rotation);
}
void Player::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_sprite);
}
void Player::setupSprite()
{
	if (!m_spriteTexture.loadFromFile("ASSETS\\IMAGES\\player.png"))
	{
		std::cout << "problem loading sprite" << std::endl;
	}
	m_sprite.setTexture(m_spriteTexture);
	m_sprite.setOrigin(m_spriteTexture.getSize().x / 2, m_spriteTexture.getSize().y / 2);
}
