#version 130

out vec4 color;

in vec3 col;
in vec2 pass_texCoords;

uniform sampler2D tex;

void main()
{
    color = texture(tex, pass_texCoords); //vec4 (col, 1.0f);
}
