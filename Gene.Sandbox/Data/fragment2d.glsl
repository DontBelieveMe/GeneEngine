#version 130

out vec4 color;

in vec3 passColor;

void main()
{
   color = vec4(passColor.rgb, 1.0f);
}
