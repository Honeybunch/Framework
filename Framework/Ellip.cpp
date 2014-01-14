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

	// Geneate points for ellipse
	int triangleCount = 0;

	for(int i = 0; i < numOfComponents - 9; i += 9)
	{
		verticies[i] = 0; //xComp
		verticies[i + 1] = 0; //yComp
		verticies[i + 2] = 0; //zcomp

		verticies[i + 3] = cos(triangleCount * PIFactor) * width;
		verticies[i + 4] = sin(triangleCount * PIFactor) * height; 
		verticies[i + 5] = 0; 

		verticies[i + 6] = cos((triangleCount + 1) * PIFactor) * width;
		verticies[i + 7] = sin((triangleCount + 1) * PIFactor) * height;
		verticies[i + 8] = 0;

		triangleCount++; 
	}

	//Generate the VAO
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	//Generate the VBO
	glGenBuffers(1, &vboID[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]); //Bind the VBO
	glBufferData(GL_ARRAY_BUFFER, numOfComponents * sizeof(GLfloat), verticies, GL_STATIC_DRAW);

	//Setup the Vertex Attributes Pointer
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

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
	glPushMatrix();

	//Load the color we want to use
	glColor4f(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());

	//We're using a vertex array
	glEnableClientState(GL_VERTEX_ARRAY);

	//Translate by the velocity
	glTranslatef(position->x + (velocity->x * interpolation), position->y + (velocity->y * interpolation), 0.0f);

	glBindVertexArray(vaoID); //Load verticies

	glDrawArrays(GL_TRIANGLES, 0, 60); //Draw verticies

	glBindVertexArray(0); //Unload verticies

	glDisableClientState(GL_VERTEX_ARRAY);

	glPopMatrix();
}