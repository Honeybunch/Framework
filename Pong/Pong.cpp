#include "Pong.h"

#include <iostream>
#include <sys/timeb.h>

using namespace std;

Pong::Pong(int screenWidth, int screenHeight) : Game(screenWidth, screenHeight)
{
	//Load sprite(s); if it fails stop and set an error code
	if (!loadMedia())
	{
		Game::setErrorCode(-3);
		return;
	}

	//Set the clear color here before we start the loop
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//Setup some FPS variables
	startTime = Game::getTimeMillis();
	frames = 1;

	//Run the main game loop!
	run();
}

bool Pong::loadMedia()
{
	//Create the ball

	//radius of 5 should do it
	float w = 20;
	float h = 20;

	//Get the position
	Vector2* pos = new Vector2((SCREEN_WIDTH/2) - (w/2), (SCREEN_HEIGHT/2) - (h/2));

	//Create the ball, and if something screws up, end it
	if (!(ball = new Ball(pos, w, h)))
		return false;
	//Then spawn the ball in
	ball->spawn(pos);

	//Create a test sprite
	kanoonoo = new Sprite(new Vector2(100,100), 50,50);
	
	//load the image in
	if (kanoonoo->init("res/images/Kanoonoo.png") != 0)
		return false;

	return true;
}

//Input Logic
void Pong::poll()
{

}

//Update Logic
void Pong::update()
{
	//Update Sprites
	ball->update(SCREEN_WIDTH, SCREEN_HEIGHT);
}

//Drawing
void Pong::render(float interpolation)
{
	//Clear
	glClear(GL_COLOR_BUFFER_BIT);

	//Render things
	ball->draw(interpolation);

	//kanoonoo->draw(interpolation);

	//Count and display FPS
	frames++;
	elapsedTime = Game::getTimeMillis() - startTime;

	framesPerSecond = float(frames) / float(elapsedTime / 1000);

	//Report FPS
	//cout << "FPS: " << framesPerSecond;

	//Clear the console 
	//windows only
	//system("cls");

	//Swap buffers
	SDL_GL_SwapWindow(Game::getSDLWindow());
}


Pong::~Pong(void)
{
	//Get rid of sprites etc.
	delete ball;
}

//Entry Point
int main(int argc, char* argv[])
{
	Pong* pong = new Pong(1280,720);

	return pong->getErrorCode();
}