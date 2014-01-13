#ifndef VECTOR_H
#define VECTOR_H

class Vector2
{
public:
	float x,y;

	Vector2(float mx, float my);

	void add(Vector2* toAdd);
	void mult(float scalar);

	~Vector2(void);
};

#endif

