#version 300 es

precision highp float;
precision highp int;

in vec3      in_Position; 
in vec3      in_Color;
in vec2      in_TextureUV;
in float     in_SamplerIndex;

out vec3     pass_Color;
out vec2     pass_TextureUV;
out float    pass_SamplerIndex;
out vec3     pass_Position;

uniform mat4 u_Projection;
uniform mat4 u_View;

void main()
{
	gl_Position     = u_View * u_Projection * vec4(in_Position, 1.0);
	pass_Color      = in_Color;
	pass_TextureUV  = in_TextureUV;
	pass_SamplerIndex  = in_SamplerIndex;
    pass_Position = in_Position;
}     
