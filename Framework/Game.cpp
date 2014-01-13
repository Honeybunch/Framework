// Pong.cpp : Defines the entry point for the console application.
//

/*
	Return Chart:
	 0 : All Good
	-1 : SDL INIT Fail
	-2 : OpenGL Context creation failure
	-3 : Sprite Creation Fail
	-4 : Font Load Fail
*/
#include "Game.h"

using namespace std;

//Setup some static variables
int Game::SCREEN_WIDTH = 0;
int Game::SCREEN_HEIGHT = 0;

//Getters / Setters
int Game::getErrorCode()
{
	return errorCode;
}

//For custom error reporting
void Game::setErrorCode(int e)
{
	errorCode = e;
}

SDL_Window* Game::getSDLWindow()
{
	return window;
}

//Constructor
Game::Game(int screenWidth, int screenHeight)
{
	Game::SCREEN_WIDTH = 1280;
	Game::SCREEN_HEIGHT = 720;

	running = true;

	window = NULL;
	screenSurface= NULL;

	errorCode = 0;

	//Initialize SDL; if it fails stop and set an error code
	if(!init())
	{
		errorCode = -1;
		return;
	}

	//Initialize OpenGL; if it fails stop and set an error code
	if(!initGL())
	{
		errorCode = -2;
		return;
	}
}

bool Game::init()
{
	//Init SDL and return false if there's an error
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL Could not Initialize! SDL Error: %s\n", SDL_GetError());
		cin.get();
		return false;
	}

	//Create the window and renderer
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL, &window, &renderer);
	SDL_GetRendererInfo(renderer, &rendererInfo);

	if(window == NULL)
	{
		printf("Window Could Not be Created! SDL Error: %s\n", SDL_GetError);
		cin.get();
		return false;
	}

	//Get the window surface
	screenSurface = SDL_GetWindowSurface(window);

	return true;
}

bool Game::initGL()
{
	//Create GL Context
	SDL_GL_CreateContext(window);

	//Get window ratio
	GLfloat ratio;
	ratio = (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT;

	//Setup viewport
	glViewport(0,0, SCREEN_WIDTH, SCREEN_HEIGHT);

	//Initialize Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Setup orthogopic view
	glOrtho(0.0,(GLdouble)SCREEN_WIDTH, (GLdouble)SCREEN_HEIGHT, 0.0, -1.0, 1.0);

	//Initialize modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glShadeModel(GL_SMOOTH);

	//Setup texture blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	//Initialize Clear Color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClearDepth(1.0f);

	//Check for an error
	GLenum error = glGetError();
	if(error != GL_NO_ERROR)
	{
		printf("Error Initializing OpenGL! %s\n", gluErrorString(error));
		cin.get();
		return false;
	}

	//Try to init glew
	GLenum glewErr = glewInit();
	if (glewErr != GLEW_OK)
	{
		printf("Error initializeing GLEW! %s\n", glewGetErrorString(glewErr));
		cin.get();
		return false;
	}

	return true;
}

//Run the main game loop
void Game::run()
{
	//Setup some timing structures
	int TICKS_PER_SECOND = 25;
	int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	int MAX_FRAMESKIP = 5;

	int nextGameTick = getTimeMillis();

	int loops = 0;
	float interpolation;

	while (running)
	{

		while (SDL_PollEvent(&keyEvent))
		{
			//Stop running when the user asks to quit
			if (keyEvent.type == SDL_QUIT)
				running = false;
		}

		//Poll input as much as possible
		poll();

		//Update the logic 25 times a second
		loops = 0;
		while (getTimeMillis() > nextGameTick && loops < MAX_FRAMESKIP)
		{
			update();

			nextGameTick += SKIP_TICKS;
			loops++;
		}

		//Calculate interpolation
		interpolation = float(getTimeMillis() + SKIP_TICKS - nextGameTick) / float(SKIP_TICKS);

		render(interpolation);
	}
}

//Return the current time in milliseconds 
int Game::getTimeMillis()
{
	timeb tb;
	ftime(&tb);
	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;
}

//Load sprites after OpenGL has been initialized
bool Game::loadMedia()
{

	return true;
}

//Free up SDL resources when the window closes
Game::~Game()
{
	//Destroy Window
	SDL_DestroyWindow(window);
	window = NULL;

	//Quit SDL
	SDL_Quit();
}
