#include "GameObject.h"

GameObject::GameObject(Vector2* pos)
{
	position = pos;
	velocity = new Vector2(0, 0);
	acceleration = new Vector2(0, 0);

	glPosition = new Vector2(0, 0);
	glVelocity = new Vector2(0, 0);
	glAcceleration = new Vector2(0, 0);
}

//For modifying the transformation matrix

void GameObject::translate(Vector2* location)
{
	transformation.m[0][3] = location->x;
	transformation.m[1][3] = location->y;
}

void GameObject::rotate(float angle)
{
	rotation.m[0][0] = cosf(angle); rotation.m[0][1] = -sinf(angle);
	rotation.m[1][0] = sinf(angle); rotation.m[1][1] = cosf(angle);
}

void GameObject::scale(float xScale, float yScale, float zScale)
{
	scaling.m[0][0] = xScale;
	scaling.m[1][1] = yScale;
	scaling.m[2][2] = zScale;
}

//Almost every GameObject will need to load its own shaders
GLuint GameObject::LoadShader(const char* vertexPath, const char* fragmentPath)
{
	//Create shaders
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//Read the Vertex Shader code
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertexPath, std::ios::in);
	if (vertexShaderStream.is_open())
	{
		std::string line = "";
		while (getline(vertexShaderStream, line))
			vertexShaderCode += "\n" + line;
		vertexShaderStream.close();
	}
	else
		std::cout << "Vertex Shader Code not found!" << std::endl;

	//Read the Fragment Shader code
	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragmentPath, std::ios::in);
	if (fragmentShaderStream.is_open())
	{
		std::string line = "";
		while (getline(fragmentShaderStream, line))
			fragmentShaderCode += "\n" + line;
		fragmentShaderStream.close();
	}
	else
		std::cout << "Fragment Shader Code not found!" << std::endl;

	//Time to compile shaders
	GLint result = GL_FALSE;
	int infoLogLength;

	//Compile Vertex Shader
	printf("Compiling Vertex Shader: %s\n", vertexPath);
	char const* vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
	glCompileShader(vertexShaderID);

	//Check Vertex Shader
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	GLchar* vertexShaderErrorMessage = new GLchar[infoLogLength + 1];
	glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, vertexShaderErrorMessage);
	fprintf(stdout, "%s\n", vertexShaderErrorMessage);

	//Compile Fragment Shader
	printf("Compiling Fragment Shader: %s\n", fragmentPath);
	char const* fragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
	glCompileShader(fragmentShaderID);

	//Check Fragment Shader
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	GLchar* fragmentShaderErrorMessage = new GLchar[infoLogLength + 1];
	glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, fragmentShaderErrorMessage);
	fprintf(stdout, "%s\n", fragmentShaderErrorMessage);

	//Link the GL Program
	fprintf(stdout, "Linking Program\n");
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	//Check program
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	GLchar* programErrorMessage = new GLchar[infoLogLength + 1];
	glGetProgramInfoLog(programID, infoLogLength, NULL, programErrorMessage);
	fprintf(stdout, "%s\n", programErrorMessage);
	
	//Dispose of shaders
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	//Delete some other things
	delete[] vertexShaderErrorMessage;
	delete[] fragmentShaderErrorMessage;
	delete[] programErrorMessage;

	return programID;
}


GameObject::~GameObject(void)
{
	delete position;
}

//Not used yet
void GameObject::update()
{

}

//We have no standard draw procedures yet
void GameObject::draw(){}