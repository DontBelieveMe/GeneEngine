#version 300 es

precision highp float;
precision highp int;

out vec4 out_Color;

in vec3 pass_Color;
in vec2 pass_TextureUV;
in float pass_SamplerIndex;
in vec3 pass_Position;

uniform sampler2D u_Textures[32];

vec4 GetTextureSample(in int index, in vec2 uv)
{
    vec4 color;
    switch(index) {
        case 0: color = texture(u_Textures[0], uv); break;
        case 1: color = texture(u_Textures[1], uv); break;
        case 2: color = texture(u_Textures[2], uv); break;
        case 3: color = texture(u_Textures[3], uv); break;
        case 4: color = texture(u_Textures[4], uv); break;
        case 5: color = texture(u_Textures[5], uv); break;
        case 6: color = texture(u_Textures[6], uv); break;
        case 7: color = texture(u_Textures[7], uv); break;
        case 8: color = texture(u_Textures[8], uv); break;
        default: color = texture(u_Textures[0], uv); break;
    }
    
    return color;
}

struct PointLightSource {
	vec3 Position;
	float Size;
	float Intensity;
	vec3 Color;	
    float Falloff;
};

uniform PointLightSource u_Lights[4];
uniform float            u_Ambient;

void main()
{
    int index = int(pass_SamplerIndex);
	vec4 color = texture(u_Textures[index], pass_TextureUV) * vec4(pass_Color.xyz, 1.0f);
    vec4 ambient = vec4(u_Ambient,u_Ambient,u_Ambient,1.0f);
	
	vec4 totalB = vec4(0.0);
	for(int i=0;i<4;i++) {
		if(u_Lights[i].Size > 0.f) {
            float dist = length(pass_Position.xy - u_Lights[i].Position.xy);
            float percent = clamp(1.0f - dist / u_Lights[i].Size, 0.1, 1.0f);
            percent *= pow(percent, u_Lights[i].Falloff) * u_Lights[i].Intensity;
            vec4 b = vec4(percent,percent,percent,percent) * vec4(u_Lights[i].Color, 1.0);
            totalB += b;
        }
	}
	
    out_Color = color * (ambient + totalB);
}
