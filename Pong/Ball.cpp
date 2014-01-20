#include "Ball.h"
#include <ctime>

#include <iostream>
using namespace std;

Ball::Ball(Vector2* pos, float width, float height) : Ellip(pos, width, height, new Color(1.0f, 1.0f, 1.0f, 1.0f))
{

}

void Ball::spawn(Vector2* pos)
{
	//Set the position (normally would be in center of screen)
	position = pos;

	//Set a random velocity

	//Seed the random
	srand(time(0));

	//Generate a random magnitude
	float mag = rand() % 5 + 5; 

	//Generate random unit vector coordinates
	float randX = -1 + (((float)rand() / (float)RAND_MAX) / (.5f));
	float randY = -1 + (((float)rand() / (float)RAND_MAX) / (.5f));

	//Apply the magnitude to the unit vector coords
	randX *= mag;
	randY *= mag;

	//We have a velocity in a random direction with a magnitude from 1-5
	velocity = new Vector2(randX, randY);
}

void Ball::update(int screenWidth, int screenHeight)
{
	//Handle bounds
	if ((position->y - Ellip::height / 2) < 0)
		velocity->y *= -1;
	else if ((position->y + Ellip::height / 2) > screenHeight)
		velocity->y *= -1;

	if ((position->x - Ellip::width / 2) < 0)
		velocity->x *= -1;
	else if ((position->x + Ellip::width / 2) > screenWidth)
		velocity->x *= -1;

	//Add velocity to position every frame;
	position->add(velocity); //This will do nothing more than keep the inner coordinates up to date; OpenGL will draw slightly differently

	GameObject::update();
}

Ball::~Ball()
{
}
