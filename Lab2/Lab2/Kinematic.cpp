#include "Kinematic.h"

float Kinematic::getNewOrientation(float t_orientation, sf::Vector2f t_velocity, sf::Vector2f t_position)
{
	if (vectorLength(t_velocity) > 0)
	{
		return toDegrees(atan2(-t_position.x, t_position.y));
	}
	else
	{
		return t_orientation;
	}
}

float Kinematic::vectorLength(sf::Vector2f t_velocity)
{
	return sqrtf(powf(t_velocity.x, 2.0f) + powf(t_velocity.y, 2.0f));
}

float Kinematic::toDegrees(float t_rads)
{
	return t_rads * PI / 180;
}
