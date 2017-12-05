#version 130

out vec4 color;

in vec3 passColor;
in vec2 passUv;
in float passTexId;
in float passVertexType;

uniform sampler2D textureSamplers[32];

void main()
{
    if(passTexId < 0)
    {
        color = vec4(passColor.rgb, 1.0f);
    } else {
        int index = int(passTexId);

        switch(index) {
            case 0: color = texture(textureSamplers[0], passUv); break;
            case 1: color = texture(textureSamplers[1], passUv); break;
            case 2: color = texture(textureSamplers[2], passUv); break;
            case 3: color = texture(textureSamplers[3], passUv); break;
            case 4: color = texture(textureSamplers[4], passUv); break;
            case 5: color = texture(textureSamplers[5], passUv); break;
            case 6: color = texture(textureSamplers[6], passUv); break;
            case 7: color = texture(textureSamplers[7], passUv); break;
            case 8: color = texture(textureSamplers[8], passUv); break;
            default: color = texture(textureSamplers[0], passUv); break;
        }

		if(passVertexType > 0)
			color = vec4(passColor.r, passColor.g, passColor.b, color.r);
    }
}
