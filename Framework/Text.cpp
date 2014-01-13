#include "Text.h"

//Because chances we're going to have to change what the text is some time
void Text::setText(char* newText)
{
	text = newText;
}

//Fot text scaling later
void Text::setWidth(float w)
{
	width = w;
}

void Text::setHeight(float h)
{
	height = h;
}

//This constructor will initialize the text and perpare it for rendering
Text::Text(char* textBody, char* font, int fontSize, Color* c, Vector2* pos, float w, float h) : Sprite(pos, w, h)
{
	text = textBody;
	fontPath = font;
	size = fontSize;
	color = c;
}

//Initialize the font and return an error if something goes wrong
int Text::init()
{
	if (!(ttfFont = TTF_OpenFont(fontPath, size)))
		return -4;
	else
		return 0;
}

void Text::draw(float interpolation)
{
	SDL_Surface* initial;
	SDL_Surface* intermediate;

	//First step is to map the font to a standard SDL surface, and then to a texture
	//We have to do this every time in case the text changes between draws
	SDL_Color sdlCol;
	sdlCol.r = color->getRed(); sdlCol.g = color->getGreen(); sdlCol.b = color->getBlue(), sdlCol.a = color->getAlpha(); //Convert our Color to an SDL_Color struct
	initial = TTF_RenderText_Blended(ttfFont, text, sdlCol);

	intermediate = SDL_CreateRGBSurface(0, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

	SDL_BlitSurface(initial, 0, intermediate, 0);

	//Generate the new texture
	glGenTextures(1, getTexture());
	glBindTexture(GL_TEXTURE_2D, *getTexture());
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_BGRA,
		GL_UNSIGNED_BYTE, intermediate->pixels);

	/* GL_NEAREST looks horrible, if scaled... */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Use the base draw function after we've set the new texture id
	Sprite::draw(interpolation);

	glDeleteTextures(1, getTexture());
}

Text::~Text()
{
}
