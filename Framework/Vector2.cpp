#include "Vector2.h"


Vector2::Vector2(float mx, float my)
{
	x = mx;
	y = my;
}

void Vector2::add(Vector2* toAdd)
{
	x += toAdd->x;
	y += toAdd->y;
}

void Vector2::mult(float scalar)
{
	x *= scalar;
	y *= scalar;
}

Vector2::~Vector2(void)
{
}
