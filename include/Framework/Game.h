#ifndef GAME_H
#define GAME_H

/*
#include "Quad.h"
#include "Ellip.h"
#include "Sprite.h"
#include "Text.h"
#include "Vector2.h"
*/

#include <stdio.h>
#include <iostream>
#include <sys\timeb.h>
#include <string>
#include <GL\glew.h>
#include <SDL2\SDL.h>
#include <SDL2\SDL_ttf.h>
#include <SDL2\SDL_mixer.h>
#include <SDL2\SDL_opengl.h>
#include <GL\GLU.h>

class Game{

public:
	bool running;

	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;

private :
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_RendererInfo rendererInfo;
	SDL_Event keyEvent;
	SDL_Surface* screenSurface;

	int errorCode;

public:
	Game(int screenWidth, int screenHeight);
	virtual ~Game();

	int getErrorCode();
	void setErrorCode(int e);

	SDL_Window* getSDLWindow();

	int getTimeMillis();

	virtual bool loadMedia();

	virtual void poll() = 0;
	virtual void update() = 0;
	virtual void render(float interpolation) = 0;

	void run();

private:
	bool init();
	bool initGL();
};
#endif