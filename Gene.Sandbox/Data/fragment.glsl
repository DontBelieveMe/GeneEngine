#version 130

out vec4 color;

uniform sampler2D texture_Sampler;

in vec3 pass_normal;
in vec3 pass_position;

void main()
{
    color = vec4(pass_position, 0.f);
}
