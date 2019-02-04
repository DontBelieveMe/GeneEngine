#section vertex
#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;
layout(location = 2) in vec2 in_uv;

out vec3 pass_color;
out vec2 pass_uv;

void main() 
{
	gl_Position = vec4(in_position.x, in_position.y, in_position.z, 1.0);
	pass_color = in_color;
	pass_uv = in_uv;
}

#section pixel
#version 330 core

out vec4 out_fragColor;

in vec3 pass_color;
in vec2 pass_uv;

uniform sampler2D u_sampler;

void main()
{
	out_fragColor = vec4(pass_color, 1.0f);
}