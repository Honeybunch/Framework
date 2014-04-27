#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
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

	void translate(Vector2* location);
	void rotate(float angle);
	void scale(float xScale, float yScale, float zScale);

	virtual void update();
	virtual void draw();

protected:
	float width, height;

	//The position, velocity and acceleration in pixels
	Vector2* position;
	Vector2* velocity;
	Vector2* acceleration;

	//The position, velocity and acceleration in GL units
	Vector2* glPosition;
	Vector2* glVelocity;
	Vector2* glAcceleration;

	Matrix4f scaling;
	Matrix4f rotation;
	Matrix4f transformation;

	//For OpenGL / GLSL
	GLuint program;

	//GLSL locations
	GLuint gScalingLocation;
	GLuint gRotationLocation;
	GLuint gTransformationLocation;
	GLuint gColorLocation;

	GLuint vboID[1]; //The IDs for the vertex buffer objects
	GLuint vaoID; //The ID for the vertex array object
};

#endif

