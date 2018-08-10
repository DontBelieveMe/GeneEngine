#version 300 es

precision highp float;
precision highp int;

in vec3      in_Position; 
in vec3      in_Color;
in vec2      in_TextureUV;
in float     in_TextureID;

out vec3     pass_Color;
out vec2     pass_TextureUV;
out float    pass_TextureID;
out vec3     pass_Position;

uniform mat4 u_Projection;
uniform mat4 u_View;

void main()
{
	gl_Position     = u_View * u_Projection * vec4(in_Position, 1.0);
	pass_Color      = in_Color;
	pass_TextureUV  = in_TextureUV;
	pass_TextureID  = in_TextureID;
    pass_Position = in_Position;
}     
