#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "GameObject.h"

class Ellip : public GameObject
{
public:
	Ellip(Vector2* pos, float w, float h);
	Ellip(Vector2* pos, float w, float h, Color* c);
	~Ellip(void);

	void initVerticies();

	void setWidth(float w);
	void setHeight(float h);

	//Per Frame
	void draw(float interpolation);

protected:
	float width, height;
	Color* color;

	//GLSL Locations
	GLuint gColorLocation;
};

#endif

