#version 130

in vec3 position; 
in vec3 color;

out vec3 passColor;

uniform mat4 u_Projection = mat4(1.0f);

void main()
{
	gl_Position = vec4(position, 1.0);
	passColor = color;
}     
