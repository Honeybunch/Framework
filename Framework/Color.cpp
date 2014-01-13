#include "Color.h"

//If colors are given as ints from 0-255, must divide by 255 to get proper float value
Color::Color(int r, int g, int b, int a = 255)
{
	red = r/255.0f;
	green = g/255.0f;
	blue = b/255.0f;
	alpha = a/255.0f;
}


Color::Color(float r, float g, float b, float a = 1.0f)
{
	red = r;
	green = g;
	blue = b;
	alpha = a;
}

Color::Color(int hex, float a = 1.0f)
{
	red = ((hex >> 16) & 0xff) / 255.0f;
	green = ((hex >> 8) & 0xff) / 255.0f;
	blue = (hex & 0xff) / 255.0f;
	
	alpha = a;
}

Color::~Color(void)
{
}


float Color::getRed(){return red;}
float Color::getGreen(){return green;}
float Color::getBlue(){return blue;}
float Color::getAlpha(){return alpha;}

void Color::setRed(int r){red = r/255.0f;}
void Color::setRed(float r){red = r;}

void Color::setGreen(int g){green = g/255.0f;}
void Color::setGreen(float g ){green = g;}

void Color::setBlue(int b){blue = b/255.0f;}
void Color::setBlue(float b){blue = b;}

void Color::setAlpha(int a){alpha = a/255.0f;}
void Color::setAlpha(float a){alpha = a;}