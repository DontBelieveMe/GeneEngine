#section vertex
#version 330 core

layout(location = 0) in vec3 in_position;

out vec3 pass_position;

uniform mat4 u_projection;
uniform mat4 u_transform = mat4(1.0);

void main() 
{
	gl_Position = u_projection * u_transform * vec4(in_position.x, in_position.y, in_position.z, 1.0);
	pass_position = in_position;
}

#section pixel
#version 330 core

out vec4 out_fragColor;
in vec3 pass_position;

void main()
{
	out_fragColor = vec4(pass_position, 1.0);
}