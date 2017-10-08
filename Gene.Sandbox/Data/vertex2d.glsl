#version 130

in vec3 position; 
in vec3 color;

out vec3 passColor;

uniform mat4 u_Projection;

void main()
{
	gl_Position = u_Projection * vec4(position, 1.0);
	passColor = color;
}     
