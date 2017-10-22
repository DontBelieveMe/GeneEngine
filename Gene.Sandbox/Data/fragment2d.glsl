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
		for(int i = 0; i < 32; i++)
		{
			if(i == index)
			{
				vec4 col = texture(textureSamplers[i], passUv);
				col.a = 1.0;
				color = col * vec4(passColor, 1.0);
				break;
			}
		}
    }
}
