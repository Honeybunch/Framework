#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "GameObject.h"

class Quad : public GameObject
{
public:
	Quad(Vector2* pos, float w, float h);
	Quad(Vector2* pos, float w, float h, Color* c);
	~Quad(void);

	void initVerticies();

	void setColor(Color* c);

	//Per Frame
	void draw(float interpolation); //From GameObject

protected:
	Color* color;
};

#endif

