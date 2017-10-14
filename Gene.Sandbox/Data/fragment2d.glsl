#version 130

out vec4 color;

in vec3 passColor;
in vec2 passUv;
in float passTexId;

uniform sampler2D textureSampler;

void main()
{
   color = texture(textureSampler, passUv); //vec4(passColor.rgb, 1.0f);
}
