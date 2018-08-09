#version 130

out vec4 out_Color;

in vec3 pass_Color;
in vec2 pass_TextureUV;
in float pass_TextureID;

uniform sampler2D u_Textures[32];

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

void main()
{
    int index = int(pass_TextureID);
    out_Color = GetTextureSample(index, pass_TextureUV) * vec4(pass_Color, 1);
}
