#version 300 es

precision highp float;
precision highp int;

out vec4 out_Color;

in vec3 pass_Color;
in vec2 pass_TextureUV;
in float pass_TextureID;
in vec3 pass_Position;

uniform sampler2D u_Textures[16];

uniform vec4 u_LightPos;

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

float map(float value, float min1, float max1, float min2, float max2) {
    float perc = (value - min1) / (max1 - min1);
    value = perc * (max2 - min2) + min2;
    return value;
}

void main()
{
    const float LightSize = 50.0f;
    int index = int(pass_TextureID);
    /*
    out_Color *= vec4(1.0f, 0.0f, 1.0f, 1.0f);*/

    float dist = length(gl_FragCoord.xy - u_LightPos.xy);
    float max_dist = 70.0f;
    float percent = clamp(1.0f - dist / max_dist, 0.0f, 1.0f);
    vec4 amb = vec4(percent, percent, percent, 1.0f);
    out_Color = GetTextureSample(index, pass_TextureUV) * vec4(pass_Color, 1) * amb;
    

}
