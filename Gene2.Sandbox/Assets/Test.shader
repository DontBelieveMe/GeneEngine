#section vertex
#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;

out vec3 pass_color;

void main() 
{
	gl_Position = vec4(in_position.x, in_position.y, in_position.z, 1.0);
	pass_color = in_color;
}

#section pixel
#version 330 core

out vec4 out_fragColor;

in vec3 pass_color;

void main()
{
	out_fragColor = vec4(pass_color, 1.0f);
}