#version 130

in vec3 position;
in vec2 uv;

uniform mat4 u_Projection;
uniform mat4 u_Transform;

out vec3 col;
out vec2 pass_texCoords;

void main()
{
	col = position;
	pass_texCoords = uv;
    gl_Position = u_Projection * u_Transform * vec4(position, 1.0);
}     
