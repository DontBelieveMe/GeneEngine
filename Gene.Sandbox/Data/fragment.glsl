#version 130

in vec3 pass_Color;
in vec2 pass_Uv;

out vec4 color;

uniform sampler2D texture_Sampler;

void main()
{
    color = texture(texture_Sampler, pass_Uv) * vec4(pass_Color, 1.0f);
}
