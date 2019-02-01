#section vertex
#version 330 core

layout (location = 0) in vec3 in_position;

void main() {
	gl_Position = vec4(in_position.x, in_position.y, in_position.z, 1.0);
}

#section pixel
#version 330 core

out vec4 out_fragColor;

void main()
{
	out_fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}