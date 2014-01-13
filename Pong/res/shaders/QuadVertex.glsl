#version 330 core

layout (location = 0) in vec3 vertPos;

uniform vec3 objPos;
uniform vec3 velocity;
uniform vec3 acceleration;
uniform float interpolation;

//UVs
const vec2 uvs[4] = vec2[4]
(
	vec2(0,1),
	vec2(0,0),
	vec2(1,1),
	vec2(1,0)
);

//Need to pass uvs to fragment
out vec2 f_uv;

void main(void)
{
	gl_Position = vec4(objPos, 0.0) + vec4(vertPos, 1.0);
	
	f_uv = uvs[gl_VertexID];
}