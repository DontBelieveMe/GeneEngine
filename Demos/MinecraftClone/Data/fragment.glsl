#version 130

out vec4 color;

in vec3 col;
in vec2 pass_texCoords;

void main()
{
    color = vec4 (col, 1.0f);
}
