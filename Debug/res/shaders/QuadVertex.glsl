#version 330 core

//Verticies for quad

const vec4 verts[4] = vec4[4]
(
	vec4(-1, -1, 0, 1),
	vec4(1, -1, 0, 1),
	vec4(-1, 1, 0, 1),
	vec4(1, 1, 0, 1)
);

//uvs indexed the same way
const vec2 uvs[4] = vec2[4]
(
	vec2(0,0),
	vec2(1,0),
	vec2(0,1),
	vec2(1,1)
);

//Need to pass uvs to fragment
out vec2 f_uv;

void main(void)
{
	gl_Position = verts[gl_VertexID];
	f_uv = uvs[gl_VertexID];
}