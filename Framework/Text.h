#ifndef TEXT_H
#define TEXT_H

#include <SDL2\SDL.h>
#include <SDL2\SDL_ttf.h>

#include "Sprite.h"
#include "Color.h"
#include "Vector2.h"

class Text : public Sprite
{
private:
	char* text;
	char* fontPath;
	int size;
	Color* color;

	//The actual TTF Font
	TTF_Font* ttfFont;

public:
	void setText(char* newText);
	void setWidth(float w);
	void setHeight(float h);

	Text(char* textBody, char* font, int fontSize, Color* c, Vector2* pos, float w, float h);

	int init();
	void draw(float interpolation);

	virtual ~Text();
};

#endif