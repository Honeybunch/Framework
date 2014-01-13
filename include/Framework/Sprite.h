#ifndef SPRITE_H
#define SPRITE_H

#include "GameObject.h"

using namespace std;

class Sprite : public GameObject
{
public:
	GLuint* getTexture();
	void setTexture(GLuint tex);

	Sprite(Vector2* pos, float w, float h);

	int init(string filePath);

	void update();
	void draw(float interpolation);

	virtual ~Sprite(void);

private:
	GLuint texture;

	bool loadMedia(string filePath);
	void initVerticies();
	
};

#endif

