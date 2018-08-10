#version 300 es

precision highp float;
precision highp int;

out vec4 out_Color;

in vec3 pass_Color;
in vec2 pass_TextureUV;
in float pass_TextureID;
in vec3 pass_Position;

uniform sampler2D u_Textures[16];


vec4 GetTextureSample(in int index, in vec2 uv)
{
    vec4 color;
    switch(index) {
        case -1: color = vec4(1.0,1.0,1.0,1.0); break;
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
uniform vec3 u_LightPositions[4];
uniform float u_LightSizes[4];
uniform float u_LightIntensitys[4];
uniform vec3 u_LightColors[4];
uniform float u_LightFalloffs[4];

struct PointLightSource {
	vec3 Position;
	float Size;
	float Intensity;
	vec3 Color;
	
}

float map(float value, float min1, float max1, float min2, float max2) {
    float perc = (value - min1) / (max1 - min1);
    value = perc * (max2 - min2) + min2;
    return value;
}

void main()
{
	int index = int(pass_TextureID);
	vec4 color = GetTextureSample(index, pass_TextureUV);

    const float AMBIENT = 0.2;
    vec4 ambient = vec4(AMBIENT,AMBIENT,AMBIENT,1.0);
	
	vec4 totalB = vec4(0.0);
	for(int i=0;i<4;i++) {
		float dist = length(pass_Position.xy - u_LightPositions[i].xy);
		float percent = clamp(1.0f - dist / u_LightSizes[i], 0.0f, 1.0f);
		percent *= pow(percent, u_LightFalloffs[i]) * u_LightIntensitys[i];
		vec4 b = vec4(percent,percent,percent,1.0) * vec4(u_LightColors[i], 1.0);
		totalB += b;
	}
	
    out_Color = color * (totalB + ambient);
}
