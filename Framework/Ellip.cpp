#include "Ellip.h"

Ellip::Ellip(Vector2* pos, float w, float h) : GameObject(pos)
{
	position = pos;
	width = w;
	height = h;
	color = new Color(0,0,0,255); //default color: black

	initVerticies();
}

Ellip::Ellip(Vector2* pos, float w, float h, Color* c) : GameObject(pos)
{
	position = pos;
	width = w;
	height = h;
	color = c;

	initVerticies();
}


Ellip::~Ellip(void)
{
}


void Ellip::initVerticies()
{
	//20 triangles should be enough; that's 60 components
	int numOfTriangles = 20;
	int numOfComponents = numOfTriangles * 9;

	float* verticies = new float[numOfComponents];

	float PIFactor = ((M_PI * 2) / (numOfTriangles - 1));

	//Need to map the width of the object to the units used by OpenGL (-1 - 1)
	float glWidth = width / Game::SCREEN_WIDTH;
	float glHeight = height / Game::SCREEN_HEIGHT;

	// Geneate points for ellipse
	int triangleCount = 0;

	for(int i = 0; i < numOfComponents - 9; i += 9)
	{
		verticies[i] = -1; //xComp
		verticies[i + 1] = 1 ; //yComp
		verticies[i + 2] = 0; //zcomp

		verticies[i + 3] = -1 + (cos(triangleCount * PIFactor) * glWidth);
		verticies[i + 4] = 1 + (sin(triangleCount * PIFactor) * glHeight);
		verticies[i + 5] = 0; 

		verticies[i + 6] = -1 + (cos((triangleCount + 1) * PIFactor) * glWidth);
		verticies[i + 7] = 1 + (sin((triangleCount + 1) * PIFactor) * glHeight);
		verticies[i + 8] = 0;

		triangleCount++; 
	}

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

void Ellip::setWidth(float w)
{
	width = w;
}

void Ellip::setHeight(float h)
{
	height = h;
}

//Per Frame

void Ellip::draw(float interpolation)
{
	//Enable things we need
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//Bind things we need
	glBindVertexArray(vaoID); 

	//Use shaders
	glUseProgram(program);

	//Modify transformation matrices
	Vector2* newPos = new Vector2(glPosition->x + (glVelocity->x * interpolation),
		glPosition->y + (glVelocity->y * interpolation));
	translate(newPos);
	delete newPos;

	//glUniformMatrix4fv(gScalingLocation, 1, GL_TRUE, &scaling.m[0][0]);
	//glUniformMatrix4fv(gRotationLocation, 1, GL_TRUE, &rotation.m[0][0]);
	//glUniformMatrix4fv(gTransformationLocation, 1, GL_TRUE, &transformation.m[0][0]);

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