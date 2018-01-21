#version 130

out vec4 color;

uniform sampler2D texture_Sampler;

in vec3 pass_position;
in vec2 pass_tex_coord;

void main()
{
    color = texture(texture_Sampler, pass_tex_coord);//vec4(pass_position, 1.0);
}
