#ifndef BALL_H
#define BALL_H

#include <Framework\Quad.h>
#include <Framework\Ellip.h>

class Ball : public Ellip
{
public:
	Ball(Vector2* pos, float width, float height);
	
	void spawn(Vector2* pos);
	virtual void update(int screenWidth, int screenHeight);

	~Ball();
};

#endif