#version 130

//in vec3 pass_Color;
//in vec2 pass_Uv;

out vec4 color;

uniform sampler2D texture_Sampler;

void main()
{
    color = vec4(1.0f, 0.0f, 1.0f, 1.0f);// * vec4(pass_Color, 1.0f);
}
