#pragma once
#include <cmath>

static class FuzzyLogic
{
public:
	static float fuzzyAnd(float t_a, float t_b);
	static float fuzzyOr(float t_a, float t_b);
	static float fuzzyNot(float t_a);
	static float fuzzyGrade(float t_value, float t_x0, float t_x1);
	static float fuzzyTriangle(float t_value, float t_x0, float t_x1, float t_x2);
	static float fuzzyTrapezoid(float t_value, float t_x0, float t_x1, float t_x2, float t_x3);
};
