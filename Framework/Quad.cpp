#include "Quad.h"


Quad::Quad(Vector2* pos, float w, float h) : GameObject(pos)
{
	width = w;
	height = h;

	//Default color is black
	color = new Color(0,0,0, 255);

	initVerticies();
}

Quad::Quad(Vector2* pos, float w, float h, Color* c) : GameObject(pos)
{
	width = w;
	height = h;
	color = c;

	initVerticies();
}

void Quad::initVerticies()
{
	//Generate verticies
	float* verticies = new float[18];

	//Need 6 verticies, to draw 2 triangles, making up one quad

	//Vert One
	verticies[0] = - (width/2);
	verticies[1] = - (height / 2);
	verticies[2] = 0; //0s for Z coordinates

	//Vert Two
	verticies[3] = - (width/2);
	verticies[4] = (height / 2);
	verticies[5] = 0;

	//Vert Three
	verticies[6] = (width / 2);
	verticies[7] = (height / 2);
	verticies[8] = 0;

	//Vert Four
	verticies[9] = (width / 2);
	verticies[10] = - (height / 2);
	verticies[11] = 0;

	//Vert Five
	verticies[12] = - (width / 2);
	verticies[13] = - (height / 2);
	verticies[14] = 0; 

	//Vert Six
	verticies[15] = (width / 2);
	verticies[16] = (height / 2);
	verticies[17] = 0;


	//Scaling Matrix
	scaling.m[0][0] = 1.0f; scaling.m[0][1] = 0.0f; scaling.m[0][2] = 0.0f; scaling.m[0][3] = 0.0f;
	scaling.m[1][0] = 0.0f; scaling.m[1][1] = 1.0f; scaling.m[1][2] = 0.0f; scaling.m[1][3] = 0.0f;
	scaling.m[2][0] = 0.0f; scaling.m[2][1] = 0.0f; scaling.m[2][2] = 1.0f; scaling.m[2][3] = 0.0f;
	scaling.m[3][0] = 0.0f; scaling.m[3][1] = 0.0f; scaling.m[3][2] = 0.0f; scaling.m[3][3] = 1.0f;

	//Rotation Matrix
	rotation.m[0][0] = 1.0f; rotation.m[0][1] = 0.0f; rotation.m[0][2] = 0.0f; rotation.m[0][3] = 0.0f;
	rotation.m[1][0] = 0.0f; rotation.m[1][1] = 1.0f; rotation.m[1][2] = 0.0f; rotation.m[1][3] = 0.0f;
	rotation.m[2][0] = 0.0f; rotation.m[2][1] = 0.0f; rotation.m[2][2] = 1.0f; rotation.m[2][3] = 0.0f;
	rotation.m[3][0] = 0.0f; rotation.m[3][1] = 0.0f; rotation.m[3][2] = 0.0f; rotation.m[3][3] = 1.0f;

	//Transformation matrix
	transformation.m[0][0] = 1.0f; transformation.m[0][1] = 0.0f; transformation.m[0][2] = 0.0f; transformation.m[0][3] = position->x / Game::SCREEN_WIDTH /2;
	transformation.m[1][0] = 0.0f; transformation.m[1][1] = 1.0f; transformation.m[1][2] = 0.0f; transformation.m[1][3] = position->y / Game::SCREEN_HEIGHT / 2;
	transformation.m[2][0] = 0.0f; transformation.m[2][1] = 0.0f; transformation.m[2][2] = 1.0f; transformation.m[2][3] = 0.0f;
	transformation.m[3][0] = 0.0f; transformation.m[3][1] = 0.0f; transformation.m[3][2] = 0.0f; transformation.m[3][3] = 1.0f;


	//Generate the VAO
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	//Generate the VBO
	glGenBuffers(1, &vboID[0]);

	//Bind the VBO for vertex data
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
	glBufferData(GL_ARRAY_BUFFER, 180 * sizeof(GLfloat), verticies, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	//Unbind VAO
	glBindVertexArray(0);

	//Load shaders
	program = LoadShader("res/shaders/Vertex.glsl", "res/shaders/ColFragment.glsl");
	glUseProgram(program);

	//Get uniform variables
	gScalingLocation = glGetUniformLocation(program, "scaling");
	gRotationLocation = glGetUniformLocation(program, "rotation");
	gTransformationLocation = glGetUniformLocation(program, "transformation");
	gColorLocation = glGetUniformLocation(program, "inColor");

	//Assign uniform variables
	glUniformMatrix4fv(gScalingLocation, 1, GL_TRUE, &scaling.m[0][0]);
	glUniformMatrix4fv(gRotationLocation, 1, GL_TRUE, &rotation.m[0][0]);
	glUniformMatrix4fv(gTransformationLocation, 1, GL_TRUE, &transformation.m[0][0]);
	glUniform4f(gColorLocation, color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());

	//Don't need to use this program anymore
	glUseProgram(0);

	//Delete unneeded data
	delete[] verticies;
}

Quad::~Quad(void)
{
	
}

//Per Frame
void Quad::draw(float interpolation)
{
	//Enable things we need
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//Bind things we need
	glBindVertexArray(vaoID); 

	//Use shaders
	glUseProgram(program);

	//Modify transformation matrices
	Vector2* newPos = new Vector2(position->x + (velocity->x * interpolation),
		position->y + (velocity->y * interpolation));

	//Update new position to GL coordinates
	newPos->x = (float)(newPos->x / (Game::SCREEN_WIDTH) * 2);
	newPos->y = (float)(-newPos->y / (Game::SCREEN_HEIGHT) * 2);

	translate(newPos);
	delete newPos;

	//glUniformMatrix4fv(gScalingLocation, 1, GL_TRUE, &scaling.m[0][0]);
	//glUniformMatrix4fv(gRotationLocation, 1, GL_TRUE, &rotation.m[0][0]);
	glUniformMatrix4fv(gTransformationLocation, 1, GL_TRUE, &transformation.m[0][0]);

	//Render
	glDrawArrays(GL_TRIANGLES, 0, 60); //Draw verticies

	//No longer need shaders
	glUseProgram(0);

	//Disable things we don't need
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//Unbind things we no longer need
	glBindVertexArray(0);
}