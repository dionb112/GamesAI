#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
const static float PI = 3.14159265359;
const static float ONE_RAD = 180 / PI;
class Kinematic 
{
public:
	float static getNewOrientation(float t_orientation, sf::Vector2f t_velocity, sf::Vector2f t_position);
	float static vectorLength(sf::Vector2f t_velocity);
	float static toDegrees(float t_rads);
};