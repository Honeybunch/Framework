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

//Structs we may need for game objects
struct Matrix4f
{
	float m[4][4];
};

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

	Matrix4f transform;

	//For OpenGL / GLSL
	GLuint program;

	//GLSL locations
	GLuint gTransformLocation;

	GLuint vboID[1]; //The IDs for the vertex buffer objects
	GLuint vaoID; //The ID for the vertex array object
};

#endif

