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


	//Generate the VAO
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	//Generate the VBO
	glGenBuffers(1, &vboID[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]); //Bind the VBO
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), verticies, GL_STATIC_DRAW);

	//Setup the Vertex Attributes Pointer
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	delete [] verticies;
}

Quad::~Quad(void)
{
	
}

//Per Frame

void Quad::draw(float interpolation)
{
	glPushMatrix();

	//Load the color we want to use
	glColor4f(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());

	//We're using a vertex array
	glEnableClientState(GL_VERTEX_ARRAY);

	//Translate by the velocity
	glTranslatef(position-> x  + (velocity->x * interpolation), position->y + (velocity->y * interpolation), 0.0f);

	glBindVertexArray(vaoID); //Load verticies

	glDrawArrays(GL_TRIANGLES, 0, 60); //Draw verticies

	glBindVertexArray(0); //Unload verticies

	glDisableClientState(GL_VERTEX_ARRAY);

	glPopMatrix();
}