#include "FuzzyLogic.h"

float FuzzyLogic::fuzzyAnd(float t_a, float t_b)
{
	return std::fmin(t_a, t_b);
}

float FuzzyLogic::fuzzyOr(float t_a, float t_b)
{
	return std::fmax(t_a, t_b);
}

float FuzzyLogic::fuzzyNot(float t_a)
{
	return 1.0f - t_a;
}

float FuzzyLogic::fuzzyGrade(float t_value, float t_x0, float t_x1)
{
	float result;
	float x = t_value;

	if (x <= t_x0) {
		result = 0;
	}
	else if (x > t_x1) {
		result = 1;
	}
	else {
		result = ((x - t_x0) / (t_x1 - t_x0));
	}
	return result;
}

float FuzzyLogic::fuzzyTriangle(float t_value, float t_x0, float t_x1, float t_x2)
{
	float result;
	float x = t_value;

	if (x <= t_x0 || x >= t_x2) {
		result = 0;
	}
	else if (x == t_x1) {
		result = 1;
	}
	else if (x > t_x0 && x < t_x1) {
		result = ((x - t_x0) / (t_x1 - t_x0));
	}
	else {
		result = ((t_x2 - x) / (t_x2 - t_x1));
	}
	return result;
}

float FuzzyLogic::fuzzyTrapezoid(float t_value, float t_x0, float t_x1, float t_x2, float t_x3)
{
	float result;
	float x = t_value;

	if (x <= t_x0 || x >= t_x3) {
		result = 0;
	}
	else if (x >= t_x1 && x <= t_x2) {
		result = 1;
	}
	else if (x > t_x0 && x < t_x1) {
		result = ((x - t_x0) / (t_x1 - t_x0));
	}
	else {
		result = ((t_x3 - x) / (t_x3 - t_x2));
	}
	return result;
}
