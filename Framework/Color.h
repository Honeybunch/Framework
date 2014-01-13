#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <stdio.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <GL/GLU.h>

class Color
{
public:
	//Lots of possible constructors; for RGBA int, RGBA decimal, and Hex
	Color(int r, int g, int b, int a);
	Color(float r, float g, float b, float a);
	Color(int hex, float a);
	~Color(void);

	float getRed();
	float getGreen();
	float getBlue();
	float getAlpha();

	void setRed(int r);
	void setRed(float r);
	
	void setBlue(int b);
	void setBlue(float b);

	void setGreen(int g);
	void setGreen(float g);

	void setAlpha(int a);
	void setAlpha(float a);

private:
	float red;
	float green;
	float blue;
	float alpha;
};

#endif
