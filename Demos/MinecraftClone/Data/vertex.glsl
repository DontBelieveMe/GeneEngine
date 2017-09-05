#version 130

in vec3 position;
in vec2 uv;

uniform mat4 u_Projection;
uniform mat4 u_Transform;
uniform mat4 u_View;

out vec3 col;
out vec2 pass_texCoords;

void main()
{
	col = position;
	pass_texCoords = uv;
    gl_Position = u_Projection * u_Transform * u_View * vec4(position, 1.0);
}     
