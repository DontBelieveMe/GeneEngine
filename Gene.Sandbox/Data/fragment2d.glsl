#version 130

out vec4 color;

in vec3 passColor;
in vec2 passUv;
in float passTexId;

uniform sampler2D textureSamplers[32];

void main()
{
    if(passTexId < 0)
    {
        color = vec4(passColor.rgb, 1.0f);
    } else {
        int index = int(passTexId);
        // You know, because fuck non constant integral expressions for indexing sampler arrays
        if(index < 8)
        {
            if(index < 4)
            {
                if(index < 2)
                {
                    if(index == 0) color = texture(textureSamplers[0], passUv);
                    else color = texture(textureSamplers[1], passUv);
                } else
                {
                    if(index == 2) color = texture(textureSamplers[2], passUv);
                    else color = texture(textureSamplers[3], passUv);
                }
            } else {
                if(index == 4) color = texture(textureSamplers[4], passUv);
                else color = texture(textureSamplers[5], passUv);
            }
        }
    }
//    color = texture(textureSamplers[1], passUv); //vec4(passColor.rgb, 1.0f);
}
