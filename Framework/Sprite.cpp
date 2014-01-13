#include "Sprite.h"

GLuint* Sprite::getTexture()
{
	return &texture;
}

void Sprite::setTexture(GLuint tex)
{
	texture = tex;
}

Sprite::Sprite(Vector2* pos, float w, float h) : GameObject(pos)
{
	width = w;
	height = h;
}

int Sprite::init(string filePath)
{
	//Load media
	if(!loadMedia(filePath))
		return -2;

	//Setup the positions of the verticies and the texture mapping
	initVerticies();

	//Return 0 because everything went well
	return 0;
}


//Load media, and if there is an issue, return false;
bool Sprite::loadMedia(string filePath)
{
	SDL_Surface* spriteSurface = IMG_Load(filePath.c_str()); //Load with SDL_Image library
	if(spriteSurface == NULL)
	{
		printf("Unable to load resources %s! SDL Error: %s\n", filePath.c_str(), SDL_GetError());
		return false;
	}

	//Save the width and height of the texture
	width = spriteSurface->w;
	height = spriteSurface->h;

	//Once we've loaded the surface, time to generate textures
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Determine the texture format from the surface
    GLint nOfColors = spriteSurface->format->BytesPerPixel;
	GLenum textureFormat = GL_RGB; //Default to RGB
    if (nOfColors == 4)     // contains an alpha channel
    {
        if (spriteSurface->format->Rmask == 0x000000ff)
            textureFormat = GL_RGBA;
        else
            textureFormat = GL_BGRA;
    } 
	else if (nOfColors == 3)     // no alpha channel
    {
        if (spriteSurface->format->Rmask == 0x000000ff)
            textureFormat = GL_RGB;
        else
            textureFormat = GL_BGR;
    }
	else
	{
        printf("Image is not True Color; Texture cannot be loaded; Number of Colors : %d", nOfColors);
		return false;
	}

	//Set the surface to the GL texture
	glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, width, height, 0, textureFormat, GL_UNSIGNED_BYTE, spriteSurface->pixels);

	//We don't need the surface anymore
	SDL_FreeSurface(spriteSurface);

	return true;
}

void Sprite::initVerticies()
{
	//Generate verticies
	float* verticies = new float[18];

	//Need to map the width of the object to the units used by OpenGL (-1 - 1)
	float glWidth = width / Game::SCREEN_WIDTH;
	float glHeight = height / Game::SCREEN_HEIGHT;

	//Need 4 verticies, to draw 2 triangles, making up one quad

	//Vert One
	verticies[0] = -1 - (glWidth / 2);
	verticies[1] =  1 - (glHeight / 2);
	verticies[2] = 0; //0s for Z coordinates

	//Vert Two
	verticies[3] = -1 - (glWidth / 2);
	verticies[4] =  1 + (glHeight / 2);
	verticies[5] = 0;

	//Vert Three
	verticies[6] = -1 + (glWidth / 2);
	verticies[7] =  1 - (glHeight / 2);
	verticies[8] = 0;

	//Vert Four
	verticies[9] = -1 + (glWidth / 2);
	verticies[10] = 1 + (glHeight / 2);
	verticies[11] = 0;
	

	//Generate the VAO
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	
	//Generate the VBO
	glGenBuffers(1, &vboID[0]);

	//Bind the VBO for vertex data
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]); 
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), verticies, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	
	//Unbind VAO
	glBindVertexArray(0);

	//Load shaders
	program = LoadShader("res/shaders/QuadVertex.glsl", "res/shaders/QuadFragment.glsl");
	glUseProgram(program);

	//Get uniform variables
	gPosLocation = glGetUniformLocation(program, "objPos");

	//Maybe use matrix here?

	glUniform3f(gPosLocation, position->x / Game::SCREEN_WIDTH, position->y / -Game::SCREEN_HEIGHT, 0.0f);

	//Don't need to use this program anymore
	glUseProgram(0);

	//Delete unneeded data
	delete[] verticies;
}

void Sprite::update()
{

}

void Sprite::draw(float interpolation)
{
	//Translate by the velocity
	//glTranslatef(position->x + (velocity->x * interpolation), position->y + (velocity->y * interpolation), 0.0f);

	//Enable things we need
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);

	//Bind things we need
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(vaoID);

	//Use Shaders
	glUseProgram(program);
	
	//Render
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glUseProgram(0);

	//Disable things we don't need
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);

	//Unbind things we no longer need
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

Sprite::~Sprite(void)
{
	//Delete textures
	glDeleteTextures(1, &texture);

	//Free up objects
	position = NULL;
}
