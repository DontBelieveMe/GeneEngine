#version 130

in vec3 position; 
in vec3 color;
in vec2 uv;

out vec3 passColor;
out vec2 passUv;

uniform mat4 u_Projection;

void main()
{
	gl_Position = u_Projection * vec4(position, 1.0);
	passColor = color;
}     
