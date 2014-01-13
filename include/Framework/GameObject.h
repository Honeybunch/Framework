#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdio.h>

#include <GL\glew.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include "Game.h"
#include "Vector2.h"
#include "Color.h"

class GameObject
{
public:
	GameObject(Vector2* pos);
	~GameObject(void);

	GLuint LoadShader(const char* vertexPath, const char* fragmentPath);

	virtual void update();
	virtual void draw();

protected:
	float width, height;

	Vector2* position;
	Vector2* velocity;
	Vector2* acceleration;

	//For OpenGL / GLSL
	GLuint program;

	//GLSL locations
	GLuint gPosLocation;
	GLuint gVelLocation;
	GLuint gAccLocation;
	GLuint gInterpLocation;

	GLuint vboID[2]; //The IDs for the vertex buffer objects
	GLuint vaoID; //The ID for the vertex array object
};

#endif

